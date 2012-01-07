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

MEAudioDecoder::MEAudioDecoder()
{
    init();
}

MEAudioDecoder::~MEAudioDecoder()
{
    dealloc();
}

int MEAudioDecoder::init()
{
    return 0;
}

void MEAudioDecoder::dealloc()
{
    avcodec_close(incode_ctx);
    av_close_input_file(infmt_ctx);
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
    return av_read_frame(infmt_ctx,&packet);
}

QString MEAudioDecoder::getFileName()
{
    QString retval(fileName);
    return retval;
}

