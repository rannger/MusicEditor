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
#include "debug_string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

MEAudioDecoder::MEAudioDecoder()
{
    init();
}

MEAudioDecoder::~MEAudioDecoder()
{
    dealloc();
}

int MEAudioDecoder::getSuccessFlag()
{
    return successFlag;
}

int MEAudioDecoder::OpenFile(const QString &fileName)
{
    return (successFlag=initWithFile(fileName));
}

int MEAudioDecoder::init()
{
    incode_ctx=NULL;
    infmt_ctx=NULL;
    successFlag=-1;
    numberOfFrames=0;
    frameToRead=-1;
    frameCount=0;
    return 0;
}

int MEAudioDecoder::getNumberOfFrame()
{

    int retval=0;

    retval=incode_ctx->frame_number/*infmt_ctx->streams[this->audioindex]->nb_frames*/;
    retval*=1000;
    return retval;
}



void MEAudioDecoder::dealloc()
{
    if(incode_ctx)
    {
        avcodec_close(incode_ctx);
        incode_ctx=NULL;
    }
    if(infmt_ctx)
    {
        av_close_input_file(infmt_ctx);
        infmt_ctx=NULL;
    }
    fileName[0]='\0';
}

int MEAudioDecoder::decoder(QVector< short >& retData)
{
    AVPacket packet;
    av_init_packet(&packet);
    int pktsize;
    uint8_t* pktdata=NULL;

    int audio_outbuf_size = AVCODEC_MAX_AUDIO_FRAME_SIZE; //FF_MIN_BUFFER_SIZE; //outSampleSize;//inputSampleSize;//
    uint8_t *audio_outbuf = (uint8_t *)av_malloc(audio_outbuf_size); // *2 * oAcc->channels);

    int samples_size_ptr = AVCODEC_MAX_AUDIO_FRAME_SIZE;
    short *samples = (short*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
    retData.empty();
    int len;
    int retval=0;
    int test=0;
    while(readFrame(packet)>=0)
    {
        if(packet.stream_index == audioindex)
        {
                numberOfFrames++;
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
                        else
                        {

                            for(int index=0;index<samples_size_ptr;index++)
                            {
                                int16_t data=samples[index];
                                retData.push_back(data);
                            }
                        }
                }
          }
                av_free_packet(&packet);
    }
    av_free(samples);
    av_free(audio_outbuf);
    return 0;
}
int MEAudioDecoder::decoder(QVector<double>& retData)
{
    AVPacket packet;
    av_init_packet(&packet);
    int pktsize;
    uint8_t* pktdata=NULL;

    int audio_outbuf_size = AVCODEC_MAX_AUDIO_FRAME_SIZE; //FF_MIN_BUFFER_SIZE; //outSampleSize;//inputSampleSize;//
    uint8_t *audio_outbuf = (uint8_t *)av_malloc(audio_outbuf_size); // *2 * oAcc->channels);

    int samples_size_ptr = AVCODEC_MAX_AUDIO_FRAME_SIZE;
    short *samples = (short*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
    retData.empty();
    int len;
    int retval=0;
    int test=0;
    while(readFrame(packet)>=0)
    {

        if(packet.stream_index == audioindex)
        {
                numberOfFrames++;
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
                        else
                        {

                            for(int index=0;index<samples_size_ptr;index+=4096<<1)
                            {
                                int16_t data=samples[index]+(samples[index+1]<<8);
                                if(samples[index+1]&0x80)
                                    data|=0xffff0000;
                                double fdata=data/32767.0f;

                                retData.append(fdata);
                            }

                        }
                }
          }
                av_free_packet(&packet);
    }
    av_free(samples);
    av_free(audio_outbuf);
    return 0;
}

int MEAudioDecoder::SeekFrame(int64_t num)
{
    double timestamp=(double)num;
    timestamp/=1000;
    return av_seek_frame(infmt_ctx,-1,int64_t(timestamp*AV_TIME_BASE),AVSEEK_FLAG_ANY);
}

int MEAudioDecoder::initWithFile(const QString& fileName)
{
    char * infile = fileName.toLocal8Bit().data();
    strcpy(this->fileName,infile);
    char* input_file=infile;

//    AVFormatContext *infmt_ctx=NULL;

    int i = 0;

    //////////////////////// 初始化 ////////////////////////
//        avcodec_register_all();
//        avdevice_register_all();
//        av_register_all();

    //////////////////////// 输入 ////////////////////////
    infmt_ctx = av_alloc_format_context();

    //打开输入文件
    if(av_open_input_file(&infmt_ctx, input_file, NULL, 0, NULL)!=0)
    {
            debug_string("can't open input file\n");
            return -1;
    }


    //取出流信息
    if(av_find_stream_info(infmt_ctx) <0)
    {
            debug_string("can't find suitable codec parameters\n");
            return -2;
    }


    //dump_format(infmt_ctx, 0, input_file, 0); //列出输入文件的相关流信息

    // 查找音频流信息
//    int audioindex=-1;
    audioindex=-1;
    for(unsigned int j = 0; j < infmt_ctx->nb_streams; j++)
    {
            if(infmt_ctx->streams[j]->codec->codec_type == CODEC_TYPE_AUDIO)
            {
                    audioindex=j;
                    break;
            }
    }

    if(audioindex == -1) //没有找到音频流
    {
            debug_string("can't find audio stream\n");
            return -3;
    }

//    AVCodecContext *incode_ctx;
//    AVCodec *incodec;

    incode_ctx = infmt_ctx->streams[audioindex]->codec;

    //找到合适的音频解码器
    incodec = avcodec_find_decoder(incode_ctx->codec_id);
    if(incodec == NULL)
    {
            debug_string("can't find suitable audio decoder\n");
            return -4;
    }

    //打开该音频解码器
    if(avcodec_open(incode_ctx, incodec) < 0)
    {
            debug_string("can't open the audio decoder\n");
            return -5;
    }

    return 0;
}

AVCodecContext* MEAudioDecoder::getAVCodecContext()
{
    return incode_ctx;
}

AVFormatContext* MEAudioDecoder::getAVFormatContext()
{
    return infmt_ctx;
}

AVCodec* MEAudioDecoder::getAVCodec()
{
    return incodec;
}

int MEAudioDecoder::getSampleRate()
{
    return incode_ctx->sample_rate;
}

int MEAudioDecoder::getBitRate()
{
    return incode_ctx->bit_rate;
}

int MEAudioDecoder::getChannels()
{
    return incode_ctx->channels;
}

int MEAudioDecoder::readFrame(AVPacket &packet)
{

    if(frameToRead<0)
        return av_read_frame(infmt_ctx,&packet);
    if(frameCount<frameToRead)
    {
        frameCount++;
        return av_read_frame(infmt_ctx,&packet);
    }
    else
    {
        frameToRead=-1;
        frameCount=0;
        return frameToRead;
    }
    return -1;
}

QString MEAudioDecoder::getFileName()
{
    QString retval(fileName);
    return retval;
}

void MEAudioDecoder::setFrameToRead(int frame)
{
    frameToRead=frame;
    frameCount=0;
}

int MEAudioDecoder::getFrameToRead()
{
    return this->frameToRead;
}
