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
#include <QDebug>
#include "meaudiodecoder.h"

MEAudioDecoder::MEAudioDecoder()
    :pFormatCtx(NULL)
    ,pCodecCtx(NULL)
    ,pCodec(NULL)
    ,pFrame(NULL)
{
}

MEAudioDecoder::~MEAudioDecoder()
{

}

int MEAudioDecoder::OpenFile(const QString& fileName)
{
    av_register_all();
    const char * infile = fileName.toLocal8Bit().data();
    const char * outfile = "e://out.wma";
    AVFormatContext *pInFmtCtx=NULL;
    if (av_open_input_file(&pInFmtCtx, infile, NULL, 0, NULL)!=0)
    {
        qDebug()<<"av_open_input_file failed.\n";
        return 1; // Couldn't open file
    }
    if (pInFmtCtx==NULL)
    {
        qDebug()<<"av_open_input_file OK, but FormatContext==NULL";
        return 1; // Couldn't open file
    }
    if(Safe_av_find_stream_info(pInFmtCtx)<0)
    {
        qDebug()<<"av_find_stream_info failed.";
        return 2; // Couldn't find stream
    }
    unsigned int i, audioStream;
    // Find the first audio stream
    audioStream = -1;
    for(i=0; i<pInFmtCtx->nb_streams; i++)
        if(pInFmtCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
        {
            audioStream=i;
            break;
        }
    if(audioStream==-1)
    {
        qDebug()<<"input file has no audio stream";
        return 3; // Didn't find a audio stream
    }
    AVCodecContext *pInCodecCtx=NULL;
    // Get a pointer to the codec context for the audio stream
    pInCodecCtx = pInFmtCtx->streams[audioStream]->codec;
    AVCodec *pInCodec=NULL;
    // Find the decoder for the audio stream
    pInCodec = avcodec_find_decoder(pInCodecCtx->codec_id);
    if(pInCodec==NULL)
    {
         qDebug()<<"no Decoder found";
        return 4; // Codec not found
    }
    // Inform the codec that we can handle truncated bitstreams -- i.e.,
    // bitstreams where frame boundaries can fall in the middle of packets
    //if(pInCodec->capabilities & CODEC_CAP_TRUNCATED)
    //    pInCodecCtx->flags|=CODEC_FLAG_TRUNCATED;
    // Open codec
    if(avcodec_open(pInCodecCtx, pInCodec)<0)
    {
        qDebug()<<("avcodec_open failed.");
        return 5; // Could not open codec
    }
    AVOutputFormat * oFormat = guess_format(NULL,outfile,NULL);
    if (oFormat==NULL)
    {
        qDebug()<<"not found output file format";
        return 6;
    }
    AVFormatContext * oFmtCtx =  av_alloc_format_context();
    if (oFmtCtx==NULL)
    {
        qDebug()<<"av_alloc_format_context failed";
        return 7;
    }
    oFmtCtx->oformat = oFormat;
    AVStream * oStream = av_new_stream(oFmtCtx,0);
    AVCodecContext * oCodecCtx = oStream->codec;
    oCodecCtx->codec_id = oFmtCtx->oformat->audio_codec;
    oCodecCtx->codec_type = CODEC_TYPE_AUDIO;
    oCodecCtx->sample_rate = pInFmtCtx->streams[audioStream]->codec->sample_rate;
    oCodecCtx->bit_rate = pInFmtCtx->streams[audioStream]->codec->bit_rate;
    oCodecCtx->channels = pInFmtCtx->streams[audioStream]->codec->channels;
    AVCodec * pOutCodec = avcodec_find_encoder(oStream->codec->codec_id);
    // Open codec
    if(avcodec_open(oCodecCtx, pOutCodec)<0)
    {
        qDebug()<<"avcodec_open failed.";
        return 5; // Could not open codec
    }
    if (av_set_parameters(oFmtCtx, NULL) < 0)
    {
        qDebug()<<"Invalid output format parameters\n";
        return 8;
    }
    dump_format(oFmtCtx, 0, outfile, 1);
    dump_format(pInFmtCtx, 0, infile, 0);
     if (!(oFormat->flags & AVFMT_NOFILE))
     {
        if (url_fopen(&oFmtCtx->pb, outfile, URL_WRONLY) < 0)
        {
//            fprintf(stderr, "Could not open '%s'\n", outfile);
            qDebug()<<"Could not open "<<outfile;
            return 9;
        }
    }
    av_write_header(oFmtCtx);
    static AVPacket packet;
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
    av_init_packet(&packet);
    while(av_read_frame(pInFmtCtx, &packet)>=0)
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
                        pkt.size= avcodec_encode_audio(oCodecCtx, outbuf, ob_size, (short *)pinbuf);
                        pkt.pts= av_rescale_q(oCodecCtx->coded_frame->pts, oCodecCtx->time_base, oStream->time_base);
                        pkt.flags |= PKT_FLAG_KEY;
                        pkt.stream_index= oStream->index;
                        pkt.data= outbuf;
                        /* write the compressed frame in the media file */
                        if (av_write_frame(oFmtCtx, &pkt) != 0) {
                            qDebug()<<"Error while writing audio frame\n";
                            break;
                        }
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
    //avcodec_close(oStream->codec);//why error here?!
    // free the streams
    for(i = 0; i < oFmtCtx->nb_streams; i++) {
        av_freep(&oFmtCtx->streams[i]->codec);
        av_freep(&oFmtCtx->streams[i]);
    }
    if (!(oFormat->flags & AVFMT_NOFILE)) {
        // close the output file
        url_fclose(oFmtCtx->pb);
    }
    // free the stream
    av_free(oFmtCtx);
    SafeFreeCodecContext(pInCodecCtx);
    SaveCloseFormatContext(pInFmtCtx);
    qDebug()<<"Convert Action is OK!\n";

    return 0;
}

//avcodec_encode_audio()
//AVCodec *avcodec_find_encoder(enum CodecID id)
//        AVCodec *avcodec_find_decoder(enum CodecID id)
