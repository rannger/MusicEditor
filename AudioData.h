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
