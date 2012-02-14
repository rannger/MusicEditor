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

#include "asynchronous_decode.h"
#include <assert.h>
 QVector<short> AsynchronousDecoder(QString file,MEAudioDecoder *decoder)
{
    do{
         decoder->dealloc();
    }
    while(decoder->OpenFile(file)<0);
    if(decoder->getSuccessFlag()<0)
        return QVector<short>();
    QVector<short> data;

    decoder->decoder(data);
//    plot->update(data);
    qDebug()<<"decode finsih";
    return data;
}

void AsynchronousEncoder(QString file,MEAudioDecoder *decoder,int64_t time)
{
    assert(decoder);
    MEAuidoEncoder *encoder=new MEAuidoEncoder();
    assert(!(decoder->SeekFrame(time)<0));
    int ret=0;
    do{
        qDebug()<<(ret=encoder->OpenFile(file,decoder->getSampleRate(),decoder->getChannels(),decoder));
    }while(ret!=0);
    if(ret!=0)
        goto END;
    encoder->encoder(decoder);
    qDebug()<<"encode finish";
END:
    encoder->release();
    ;
}
