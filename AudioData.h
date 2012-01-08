#ifndef AUDIODATA_H
#define AUDIODATA_H
#include "qwt_headfile.h"
#include <qdebug.h>
#include <stdint.h>
class AudioData:public QwtData
{
private:
    QVector<uint8_t> data;
public:
    AudioData(const QVector<uint8_t>& aData)
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
        double retval=0.0f;
        retval=(double)(data[i]);
        qDebug()<<retval;
        return retval;
    }
};


#endif // AUDIODATA_H
