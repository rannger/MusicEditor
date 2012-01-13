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
#include "debug_string.h"
#include <assert.h>

MEAuidoEncoder::MEAuidoEncoder()
{
    init();
}

MEAuidoEncoder::~MEAuidoEncoder()
{
       dealloc();
}

int MEAuidoEncoder::init()
{
    return 0;
}

void MEAuidoEncoder::dealloc()
{
    avcodec_close(outcode_ctx);
    int i;
    /* free the streams */
    for(i = 0; i < outfmt_ctx->nb_streams; i++) {
            av_freep(&outfmt_ctx->streams[i]->codec);
            av_freep(&outfmt_ctx->streams[i]);
    }
    if (!(outfmt->flags & AVFMT_NOFILE)) {
            /* close the output file */
            url_fclose(outfmt_ctx->pb);
    }
    av_free(outfmt_ctx);

}


int MEAuidoEncoder::OpenFile(const QString& fileName,int samples_rate,int channel,MEAudioDecoder* decoder)
{
    char* outFile=fileName.toLocal8Bit().data();
    strcpy(this->fileName,outFile);


    //////////////////////// 输出 ////////////////////////
    char* output_file=outFile;
    AVFormatContext* infmt_ctx=decoder->getAVFormatContext();
    AVCodecContext* incode_ctx=decoder->getAVCodecContext();
    /* 解析输出文件的格式 */
//    AVOutputFormat *outfmt = guess_format(NULL, output_file, NULL);
    outfmt = guess_format(NULL, output_file, NULL);
    if (!outfmt) {
            qDebug()<<"Could not deduce output format from file extension: using MPEG.\n";
            outfmt = guess_format("mpeg", NULL, NULL);
    }
    if (!outfmt) {
            debug_string("Could not find suitable output format\n");
            return -6;
    }

    outfmt->audio_codec = CODEC_ID_MP3;

    /* allocate the output media context */
//    AVFormatContext *outfmt_ctx = av_alloc_format_context();
    outfmt_ctx = av_alloc_format_context();
    if (!outfmt_ctx) {
            debug_string("Memory error\n");
            return -7;
    }

    /* 保存输出文件的格式 */
    outfmt_ctx->oformat = outfmt;
    snprintf(outfmt_ctx->filename, sizeof(outfmt_ctx->filename), "%s", output_file);


//    AVCodecContext *outcode_ctx;
//    AVCodec *outcodec;
//    AVStream *audio_st = NULL/*, *video_st*/;
    //double audio_pts, video_pts;

    //if (outfmt->video_codec != CODEC_ID_NONE) {
    //	video_st = add_video_stream(outfmt_ctx, outfmt->video_codec);
    //}

    /* 输出文件的音频流编码器ID */
    if (outfmt->audio_codec != CODEC_ID_NONE) {
            audio_st = av_new_stream(outfmt_ctx, 1);

            outcode_ctx = audio_st->codec;
            outcode_ctx->codec_id = outfmt->audio_codec;
            outcode_ctx->codec_type = CODEC_TYPE_AUDIO;

            //oAcc->bit_rate =inCodecCtx->bit_rate ;
            outcode_ctx->sample_rate = samples_rate > 0 ? samples_rate : incode_ctx->sample_rate;
            outcode_ctx->channels    = channel > 0 ? channel : incode_ctx->channels;
            outcode_ctx->block_align = incode_ctx->block_align;
            if(outcode_ctx->block_align == 1 && outcode_ctx->codec_id == CODEC_ID_MP3)
                    outcode_ctx->block_align = 0;
    }
    /* 设置输出参数 */
    if (av_set_parameters(outfmt_ctx, NULL) < 0) {
            debug_string("Invalid output format parameters\n");
            return -8;
    }

    /* 列出输出文件的格式信息 */
    dump_format(outfmt_ctx, 0, output_file, 1);

    strcpy(outfmt_ctx->title, infmt_ctx->title);
    strcpy(outfmt_ctx->author, infmt_ctx->author);
    strcpy(outfmt_ctx->copyright, infmt_ctx->copyright);
    strcpy(outfmt_ctx->comment, infmt_ctx->comment);
    strcpy(outfmt_ctx->album, infmt_ctx->album);
    outfmt_ctx->year = infmt_ctx->year;
    outfmt_ctx->track = infmt_ctx->track;
    strcpy(outfmt_ctx->genre, infmt_ctx->genre);

    //dump_format(oc,0,output_file_name,1);//列出输出文件的相关流信息
    //找到合适的音频编码器
    outcodec = avcodec_find_encoder(outfmt_ctx->oformat->audio_codec);//(CODEC_ID_AAC);
    if(!outcodec)
    {
            debug_string("can't find suitable audio encoder\n");
            return -9;
    }

    if(avcodec_open(outcode_ctx, outcodec) <0)      //////////////////////////////////////////////////
    {
            debug_string("can't open the output audio codec");
            return -10;
    }

    /* now that all the parameters are set, we can open the audio and
    video codecs and allocate the necessary encode buffers */
    //if (video_st)
    //	open_video(outfmt_ctx, video_st);

    /* 打开音频编码器 */
//    uint8_t * pktdata = NULL;
//    int pktsize = 0;

    int audioSize = 128 * 1024 * 4; //AVCODEC_MAX_AUDIO_FRAME_SIZE;//audio_outbuf_size/incode_ctx->channels;
    if (outcode_ctx->frame_size <= 1)
    {
            switch(outcode_ctx->codec_id)
            {
                    case CODEC_ID_PCM_S32LE:
                    case CODEC_ID_PCM_S32BE:
                    case CODEC_ID_PCM_U32LE:
                    case CODEC_ID_PCM_U32BE:
                            audioSize <<= 1;
                            break;
                    case CODEC_ID_PCM_S24LE:
                    case CODEC_ID_PCM_S24BE:
                    case CODEC_ID_PCM_U24LE:
                    case CODEC_ID_PCM_U24BE:
                    case CODEC_ID_PCM_S24DAUD:
                            audioSize = audioSize / 2 * 3;
                            break;
                    case CODEC_ID_PCM_S16LE:
                    case CODEC_ID_PCM_S16BE:
                    case CODEC_ID_PCM_U16LE:
                    case CODEC_ID_PCM_U16BE:
                            break;
                    default:
                            audioSize >>= 1;
                            break;
            }

            outSampleSize = audioSize * 2 * outcode_ctx->channels;
    }
    else
    {
            outSampleSize = outcode_ctx->frame_size * 2 * outcode_ctx->channels;
    }

//    int audio_outbuf_size = AVCODEC_MAX_AUDIO_FRAME_SIZE; //FF_MIN_BUFFER_SIZE; //outSampleSize;//inputSampleSize;//
//    uint8_t *audio_outbuf = (uint8_t *)av_malloc(audio_outbuf_size); // *2 * oAcc->channels);

//    int samples_size_ptr = AVCODEC_MAX_AUDIO_FRAME_SIZE;
//    short *samples = (short*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
//    uint8_t *pSamples;

    /* 如果输出文件不存在, 则创建输出文件 */
    if (!(outfmt->flags & AVFMT_NOFILE)) {
            if (url_fopen(&outfmt_ctx->pb, output_file, URL_WRONLY) < 0) {
                    printf("Could not open '%s'\n", output_file);
                    return -11;
            }
    }

    return 0;
}
/*
int MEAuidoEncoder::encode(MEAudioDecoder* decoder)
{
    return ffmpeg_conver_audio(decoder->getFileName().toLocal8Bit().data(),
                                fileName,
                                decoder->getSampleRate(),
                                decoder->getChannels());
}
*/
 int MEAuidoEncoder::encoder(MEAudioDecoder* decoder)
 {

     int audio_outbuf_size = AVCODEC_MAX_AUDIO_FRAME_SIZE; //FF_MIN_BUFFER_SIZE; //outSampleSize;//inputSampleSize;//
     uint8_t *audio_outbuf = (uint8_t *)av_malloc(audio_outbuf_size); // *2 * oAcc->channels);

     int samples_size_ptr = AVCODEC_MAX_AUDIO_FRAME_SIZE;
     short *samples = (short*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
     uint8_t *pSamples=NULL;
     int audioindex=decoder->getAudioIndex();
     AVCodecContext* incode_ctx=decoder->getAVCodecContext();
     uint8_t * pktdata = NULL;
     int pktsize = 0;

     /* 写输出文件的头 */
     av_write_header(outfmt_ctx);


#ifdef WIN32
     AVFifoBuffer fifo;
     av_fifo_init(&fifo, av_fifo_size(&fifo)+samples_size_ptr);
     qDebug()<<__FILE__<<__LINE__;
#endif

#ifdef UNIX
     AVFifoBuffer *fifo=av_fifo_alloc(samples_size_ptr);

#endif

     int len=0;

     AVPacket packet;
     av_init_packet(&packet);
     qDebug()<<__FILE__<<__LINE__;
//     while(av_read_frame(infmt_ctx, &packet) >= 0)//从输入文件中读取一个包
     assert(!(decoder->SeekFrame(0)<0));
     while(decoder->readFrame(packet)>=0)
     {
             if(packet.stream_index == audioindex)
             {
                     pktsize = packet.size;
                     pktdata = packet.data;

                     if (pktsize > 0)
                     {
                             //if(&packet)
                             //samples=(short *)av_fast_realloc(samples,&samples_size,FFMAX(packet.size*sizeof(*samples),AVCODEC_MAX_AUDIO_FRAME_SIZE));
                             samples_size_ptr = AVCODEC_MAX_AUDIO_FRAME_SIZE;
                             len = avcodec_decode_audio2(incode_ctx, samples, &samples_size_ptr, pktdata, pktsize);//若为音频包，解码该音频包
//                                printf("source frame number：%d\n", incode_ctx->frame_number);
                             if(len <0)
                             {
                                     debug_string("while decode audio failure\n");
                                     break;
                             };

                             if(samples_size_ptr <= 0)
                             {
                                     debug_string("samples_size_ptr small than0");
                                     continue;
                             }

                             pSamples = (uint8_t *)samples;
#ifdef WIN32
                             av_fifo_realloc(&fifo, av_fifo_size(&fifo)+samples_size_ptr);
                             //av_fifo_generic_write(&fifo, samples, samples_size_ptr, NULL);
                             av_fifo_write(&fifo, pSamples, samples_size_ptr);
#endif

#ifdef UNIX
                             int space=av_fifo_generic_write(fifo, samples, samples_size_ptr, NULL);
                             if(space!=samples_size_ptr)
                             {
                                 assert(av_fifo_realloc2(fifo, av_fifo_size(fifo)+(samples_size_ptr-space))>=0);
                                 av_fifo_generic_write(fifo, samples+space, samples_size_ptr-space, NULL);
                             }


#endif
                             uint8_t *audio_buf = (uint8_t *)malloc(outSampleSize);
                             while (/*av_fifo_read(&fifo, audio_buf, outSampleSize) == 0*/true)//(av_fifo_size(&fifo) > outSampleSize)
                             {

#ifdef WIN32
                                 int ret=0;
                                 ret=av_fifo_read(&fifo, audio_buf, outSampleSize);
                                 if(ret!=0)
                                     break;
                                 qDebug()<<__FILE__<<__LINE__;
#endif

#ifdef UNIX

                                 if(av_fifo_size(fifo)<=outSampleSize)
                                     break;
                                 qDebug()<<"read out:"<<av_fifo_generic_read(fifo, audio_buf, outSampleSize,NULL);
#endif


                                     // 如果音频帧的大小小于FF_MIN_BUFFER_SIZE，编码函数将退出
                                     if (audio_outbuf_size < FF_MIN_BUFFER_SIZE)
                                             audio_outbuf_size = FF_MIN_BUFFER_SIZE;

                                     AVPacket pkt;
                                     av_init_packet(&pkt);

                                     int ss = avcodec_encode_audio(outcode_ctx, audio_outbuf, audio_outbuf_size, (short *)audio_buf);
                                     pkt.size = ss;

//                                        printf("out frame num:%d\n", outcode_ctx->frame_number);

                                     // 时间戳在没有视频的情况下，实际上没有设置的必要
                                     if (outcode_ctx->coded_frame && outcode_ctx->coded_frame->pts != AV_NOPTS_VALUE)
                                             pkt.pts = av_rescale_q(outcode_ctx->coded_frame->pts, outcode_ctx->time_base, audio_st->time_base);

                                     pkt.flags |= PKT_FLAG_KEY;  // 设不设置好像都没有什么影响
                                     pkt.stream_index = audio_st->index;// audioindex;
                                     pkt.data = audio_outbuf;

                                     if (pkt.size >0)
                                     {
                                             if (av_write_frame(outfmt_ctx, &pkt) != 0)
                                             {
                                                     debug_string("Error while writing audio frame\n");
                                                     //return -12;
                                             }
                                     }

                                     av_free_packet(&pkt);
                             }
                     }
             }

             // Free the packet that was allocated by av_read_frame
             av_free_packet(&packet);
     }

     /* write the trailer, if any */
     av_write_trailer(outfmt_ctx);

     av_free(samples);
     av_free(audio_outbuf);
    return 0;
 }

QString MEAuidoEncoder::getFileName()
{
    QString retval(fileName);
    return retval;
}



