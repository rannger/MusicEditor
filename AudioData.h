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
#ifndef AUDIODATA_H
#define AUDIODATA_H
#include "qwt_headfile.h"
#include <qdebug.h>
#include <stdint.h>
class AudioData:public QwtData
{
private:
    QVector<double> data;
public:
    AudioData(const QVector<double>& aData)
    {
        data=aData;
    }
    AudioData(){}
public:

    virtual QwtData *copy() const
    {
        AudioData* retval=new AudioData(data);
        return retval;
    }

    virtual size_t size() const
    {
        return data.size();
    }

    virtual double x(size_t i) const
    {
        return i;
    }

    virtual double y(size_t i) const
    {
        return data[i];
    }
};


#endif // AUDIODATA_H
