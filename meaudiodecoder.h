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

#ifndef MEAUDIODECODER_H
#define MEAUDIODECODER_H
#include <QtCore>
#include "ffmpeg.h"
#include "mebaseobject.h"
class MEAudioDecoder:public MEBaseObject
{
public:
    MEAudioDecoder();
    virtual ~MEAudioDecoder();
    virtual int initWithFile(const QString& fileName);
    virtual int OpenFile(const QString& fileName);
    virtual int init();
    virtual void dealloc();
    int readFrame(AVPacket &packet);
    AVCodecContext* getAVCodecContext();
    AVFormatContext* getAVFormatContext();
    AVCodec* getAVCodec();
    int getSampleRate();
    int getBitRate();
    int getChannels();
    int getNumberOfFrame();
    QString getFileName();
    int getAudioIndex(){return audioindex;}
    int decoder(QVector<double>& retData);
    int SeekFrame(int64_t num=0);
    int getSuccessFlag();
    int decoder(QVector< short >& retData);
    void setFrameToRead(int frame);
    int getFrameToRead();
private:
    char fileName[FILENAME_MAX];
    AVFormatContext *infmt_ctx;
    AVCodecContext *incode_ctx;
    AVCodec *incodec;
    int audioindex;
    int successFlag;
    int numberOfFrames;
    int frameToRead;
    int frameCount;
};

#endif // MEAUDIODECODER_H
