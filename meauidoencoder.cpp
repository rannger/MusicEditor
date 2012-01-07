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
}


int MEAuidoEncoder::OpenFile(const QString& fileName,int sampleRate,int bitRate,int channels,MEAudioDecoder* decoder)
{
    char* outFile=fileName.toLocal8Bit().data();
    strcpy(this->fileName,outFile);

    return 0;
}

int MEAuidoEncoder::encode(MEAudioDecoder* decoder)
{
    return ffmpeg_conver_audio(decoder->getFileName().toLocal8Bit().data(),
                                fileName,
                                44100,
                                2);
}

QString MEAuidoEncoder::getFileName()
{
    QString retval(fileName);
    return retval;
}



