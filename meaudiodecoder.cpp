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
{
    init();
}

MEAudioDecoder::~MEAudioDecoder()
{
    dealloc();
}

int MEAudioDecoder::init()
{
    pInFmtCtx=NULL;
    pInCodecCtx=NULL;
    pInCodec=NULL;
    audioStreamIndex=-1;
    return 0;
}

void MEAudioDecoder::dealloc()
{
    SafeFreeCodecContext(pInCodecCtx);
    SaveCloseFormatContext(pInFmtCtx);
}

int MEAudioDecoder::initWithFile(const QString& fileName)
{
    const char * infile = fileName.toLocal8Bit().data();
    strcpy(this->fileName,infile);
    unsigned int i, audioStream;


    if (av_open_input_file(&pInFmtCtx, infile, NULL, 0, NULL)!=0)
    {
        qDebug()<<"av_open_input_file failed.\n";
        flag=-1;
        return -1; // Couldn't open file
    }
    if (pInFmtCtx==NULL)
    {
        qDebug()<<"av_open_input_file OK, but FormatContext==NULL";
        flag=-1;
        return -1; // Couldn't open file
    }
    if(Safe_av_find_stream_info(pInFmtCtx)<0)
    {
        qDebug()<<"av_find_stream_info failed.";
        flag=-1;
        return -1; // Couldn't find stream
    }

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
        flag=-1;
        return -1; // Didn't find a audio stream
    }
    audioStreamIndex=audioStream;
    // Get a pointer to the codec context for the audio stream
    pInCodecCtx = pInFmtCtx->streams[audioStream]->codec;
    // Find the decoder for the audio stream
    pInCodec = avcodec_find_decoder(pInCodecCtx->codec_id);
    if(pInCodec==NULL)
    {
         qDebug()<<"no Decoder found";
         flag=-1;
        return -1; // Codec not found
    }
    // Inform the codec that we can handle truncated bitstreams -- i.e.,
    // bitstreams where frame boundaries can fall in the middle of packets
    //if(pInCodec->capabilities & CODEC_CAP_TRUNCATED)
    //    pInCodecCtx->flags|=CODEC_FLAG_TRUNCATED;
    // Open codec
    if(avcodec_open(pInCodecCtx, pInCodec)<0)
    {
        qDebug()<<("avcodec_open failed.");
        flag=-1;
        return -1; // Could not open codec
    }

    sampleRate=pInFmtCtx->streams[audioStream]->codec->sample_rate;
    bitRate=pInFmtCtx->streams[audioStream]->codec->bit_rate;
    channels=pInFmtCtx->streams[audioStream]->codec->channels;
    dump_format(pInFmtCtx, 0, infile, 0);
    qDebug()<<"open success "<<infile;
    return 0;
}

AVCodecContext* MEAudioDecoder::getAVCodecContext()
{
    return this->pInCodecCtx;
}

AVFormatContext* MEAudioDecoder::getAVFormatContext()
{
    return this->pInFmtCtx;
}

AVCodec* MEAudioDecoder::getAVCodec()
{
    return this->pInCodec;
}

int MEAudioDecoder::getSampleRate()
{
    return this->sampleRate;
}

int MEAudioDecoder::getBitRate()
{
    return this->bitRate;
}

int MEAudioDecoder::getChannels()
{
    return this->channels;
}

int MEAudioDecoder::readFrame(AVPacket &packet)
{
    return av_read_frame(pInFmtCtx, &packet);
}

int MEAudioDecoder::getAudioStream()
{
    return this->audioStreamIndex;
}

