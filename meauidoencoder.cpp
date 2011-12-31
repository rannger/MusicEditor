/**************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

#include "meauidoencoder.h"
#include "meaudiodecoder.h"
#include <assert.h>

MEAuidoEncoder::MEAuidoEncoder()
{
    init();
}

MEAuidoEncoder::~MEAuidoEncoder()
{
    if(flag!=-1)
       dealloc();
}

int MEAuidoEncoder::init()
{
    oFmtCtx=NULL;
    oCodecCtx=NULL;
    pOutCodec=NULL;
    oFormat=NULL;
    oStream=NULL;
    return 0;
}

void MEAuidoEncoder::dealloc()
{
     avcodec_close(oCodecCtx);
    int i;
        for(i = 0; i < oFmtCtx->nb_streams; i++) {
            av_freep(&oFmtCtx->streams[i]->codec);
            av_freep(&oFmtCtx->streams[i]);
        }
        if (!(oFormat->flags & AVFMT_NOFILE)) {
            // close the output file
            url_fclose(oFmtCtx->pb);
        }
        // free the stream
        if(oFmtCtx)
            av_free(oFmtCtx);
}


int MEAuidoEncoder::OpenFile(const QString& fileName,int sampleRate,int bitRate,int channels,MEAudioDecoder* decoder)
{
    char* outFile=fileName.toLocal8Bit().data();
    bitRate=64000;
    strcat(this->fileName,outFile);
    oFormat=guess_format(NULL,outFile,NULL);
    if (oFormat==NULL)
    {
        qDebug()<<"not found output file format";
        flag=-1;
        return -1;
    }

    oFmtCtx =  av_alloc_format_context();
    if (oFmtCtx==NULL)
    {
            qDebug()<<"av_alloc_format_context failed";
            flag=-1;
            return -1;
    }

    oFmtCtx->oformat = oFormat;
    oStream = av_new_stream(oFmtCtx,1);
    oCodecCtx = oStream->codec;

    oCodecCtx->codec_id = oFmtCtx->oformat->audio_codec;
    oCodecCtx->codec_type = CODEC_TYPE_AUDIO;
    oCodecCtx->sample_rate = sampleRate;
    oCodecCtx->bit_rate = bitRate;
    oCodecCtx->channels = channels;
    oCodecCtx->sample_fmt=SAMPLE_FMT_S16;
    oCodecCtx->bit_rate_tolerance=bitRate;
//    qDebug()<<"sampleRate:"<<sampleRate;
//    qDebug()<<"bitRate:"<<bitRate;
//    qDebug()<<"channels:"<<channels;

    pOutCodec = avcodec_find_encoder(oStream->codec->codec_id);


    if(avcodec_open(oCodecCtx, pOutCodec)<0)
    {
        qDebug()<<"avcodec_open failed.";
        flag=-1;
        return -1; // Could not open codec
    }

    if (av_set_parameters(oFmtCtx, NULL) < 0)
    {
        qDebug()<<"Invalid output format parameters\n";
        flag=-1;
        return -1;
    }
    dump_format(oFmtCtx, 0, outFile, 1);

    if (!(oFormat->flags & AVFMT_NOFILE))
    {
       if (url_fopen(&oFmtCtx->pb, outFile, URL_WRONLY) < 0)
       {
           qDebug()<<"Could not open "<<outFile;
           flag=-1;
           return -1;
       }
   }
    qDebug()<<"open success "<<outFile;
    return 0;
}

int MEAuidoEncoder::encode(MEAudioDecoder* decoder)
{

        AVCodecContext* pInCodecCtx=decoder->getAVCodecContext();
        int audioStream=decoder->getAudioStream();
        AVPacket packet;
        int out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
        uint8_t * inbuf = (uint8_t *)malloc(out_size);
        uint8_t * pinbuf = NULL;
        int ob_size = FF_MIN_BUFFER_SIZE;
        uint8_t * outbuf = (uint8_t *)malloc(ob_size);
        int inputSampleSize = pInCodecCtx->frame_size * 2 * pInCodecCtx->channels;//获取Sample大小
        int outputSampleSize = oCodecCtx->frame_size * 2 * oCodecCtx->channels;//获取输出Sample大小
        uint8_t * pktdata = NULL;
        int pktsize = 0;
        int len = 0;
        int retval=0;
        int i=0;

        int audio_input_frame_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;

            /* ugly hack for PCM codecs (will be removed ASAP with new PCM
               support to compute the input frame size in samples */
            if (decoder->getAVCodecContext()->frame_size < 1)
            {
                audio_input_frame_size = out_size / decoder->getAVCodecContext()->channels;
                switch(pInCodecCtx->codec_id)
                {
                case CODEC_ID_PCM_S16LE:
                case CODEC_ID_PCM_S16BE:
                case CODEC_ID_PCM_U16LE:
                case CODEC_ID_PCM_U16BE:
                    audio_input_frame_size >>= 1;
                    break;
                default:
                    break;
                }
            }
            else
            {
                audio_input_frame_size = pInCodecCtx->frame_size;//获取Sample大小
            }
            inputSampleSize=audio_input_frame_size* 2 * pInCodecCtx->channels;
            qDebug()<<"inputSampleSize:"<<inputSampleSize;
        av_init_packet(&packet);
        av_write_header(oFmtCtx);
        int flag=0;
        while(decoder->readFrame(packet)>=0)
        {
                    // Is this a packet from the audio stream?
                    if(packet.stream_index==audioStream)
                    {
                        pktdata = packet.data;
                        pktsize = packet.size;
                        while (pktsize>0)
                        {
                            out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
                            len = avcodec_decode_audio2(pInCodecCtx,(short *)inbuf,&out_size,pktdata,pktsize);
                            if (len<0)
                            {
                                qDebug()<<"Error while decoding.\n";
                                retval=-1;
                                break;
                            }

                            if (out_size>0)
                            {
                                pinbuf = inbuf;
                                for (i=0;i<out_size;i+=inputSampleSize)
                                {
                                    AVPacket pkt;
                                    av_init_packet(&pkt);
                                    ob_size = FF_MIN_BUFFER_SIZE;
                                    pkt.size= avcodec_encode_audio(oCodecCtx, outbuf, out_size, (short *)pinbuf);
                                    if(pkt.size<0)
                                    {
                                        break;
                                    }

                                    pkt.pts= av_rescale_q(oCodecCtx->coded_frame->pts, oCodecCtx->time_base, oStream->time_base);
                                    pkt.flags |= PKT_FLAG_KEY;
                                    pkt.stream_index= oStream->index;
                                    pkt.data= outbuf;
                                    /* write the compressed frame in the media file */
                                    if (av_write_frame(oFmtCtx, &pkt) != 0) {
                                        qDebug()<<"Error while writing audio frame\n";
                                        retval=-1;
                                        break;
                                    }
                                    av_free_packet(&pkt);
                                    pinbuf += inputSampleSize;
                                }
                            }
                            pktsize -= len;
                            pktdata += len;
                        }
                    }
                    // Free the packet that was allocated by av_read_frame
                    av_free_packet(&packet);
        }
        free(inbuf);
        free(outbuf);
        av_write_trailer(oFmtCtx);

        qDebug()<<"encode end";
    return retval;
}


