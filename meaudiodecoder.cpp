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
}

int MEAudioDecoder::initWithFile(const QString& fileName)
{
    const char * infile = fileName.toLocal8Bit().data();
    strcpy(this->fileName,infile);

    return 0;
}

AVCodecContext* MEAudioDecoder::getAVCodecContext()
{
    return 0;
}

AVFormatContext* MEAudioDecoder::getAVFormatContext()
{
    return 0;
}

AVCodec* MEAudioDecoder::getAVCodec()
{
    return 0;
}

int MEAudioDecoder::getSampleRate()
{
    return 0;
}

int MEAudioDecoder::getBitRate()
{
    return 0;
}

int MEAudioDecoder::getChannels()
{
    return 0;
}

int MEAudioDecoder::readFrame(AVPacket &packet)
{
    return 0;
}

int MEAudioDecoder::getAudioStream()
{
    return 0;
}

QString MEAudioDecoder::getFileName()
{
    QString retval(fileName);
    return retval;
}
