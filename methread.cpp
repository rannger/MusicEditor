#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "methread.h"
#include "mainwindow.h"
#include "config.h"
#include "sndfile.h"
#include "madfunction.h"
#include "lame.h"

METhread::METhread(QObject *parent) :
    QThread(parent)
  , m_threadParament(NULL)
{
}

void METhread::run()
{
        qDebug()<<"thread begin";
        if(NULL==m_threadParament)
            return;
        QTableWidget* musicTable=(QTableWidget*)m_threadParament;
        QString fileName=musicTable->currentItem()->text();

        wav2Mp3(fileName);
//        mp32wav(fileName);
        qDebug()<<"thread end";
}

QObject* METhread::getThreadParam()const
{
    return m_threadParament;
}

void METhread::setThreadParam(QObject* param)
{

    m_threadParament=param;
}


void METhread::wav2Mp3(const QString& fileName)
{
    SNDFILE *sndfile=NULL;
    SF_INFO info;
    lame_global_flags *gfp;
    int mp3BufferSizeInBytes=0;
    int bufferSizeInSamples=0;
    float *buffer_l=NULL,*buffer_r=NULL;
    unsigned char* mp3buffer=NULL;
    float buffer[1024];
    sf_count_t count=0;
    char* name=(OS_IS_WIN32?fileName.toLocal8Bit().data():
                       fileName.toUtf8().data());
    int num_samples = 0;

    memset(&info,0,sizeof(info));
    //qDebug()<<"opening "<<"<<<"<<name;
    sndfile=sf_open(name,SFM_READ,&info);
    if(sndfile)
    {
        gfp = lame_init();
        lame_set_num_channels(gfp,info.channels);
        lame_set_in_samplerate(gfp,info.samplerate);
        lame_set_brate(gfp,128);
        lame_set_mode(gfp,JOINT_STEREO);
        lame_set_quality(gfp,2);
        if(lame_init_params(gfp)<0)
            goto ERROR_EXIT;
        else
        {
            qDebug()<<"lame_init_params success";
        }

        while((count=sf_read_float(sndfile,buffer,1024))>0)
        {

            bufferSizeInSamples=count/16*8/2;
            qDebug()<<"bufferSizeInSamples"<<bufferSizeInSamples;
            mp3BufferSizeInBytes = 1.25 * bufferSizeInSamples + 7200;

            mp3buffer  = (unsigned char*)malloc(sizeof(unsigned char) * mp3BufferSizeInBytes);
            buffer_l = (float*) malloc(sizeof(float) * bufferSizeInSamples);
            buffer_r = (float*) malloc(sizeof(float) * bufferSizeInSamples);

            switch (info.channels)
            {
                case 2:
                  for (int i = 0; i < bufferSizeInSamples; i++)
                  {
                        buffer_l[i] = buffer[i*info.channels];
                        buffer_r[i] = buffer[i*info.channels+1];
                  }
                  break;
                default:
                  goto ERROR_EXIT;
            }
            int retval = lame_encode_buffer_float(  gfp,
                                                    buffer_l,
                                                    buffer_r,
                                                    bufferSizeInSamples,      // number of samples per channel
                                                    mp3buffer,                  // pointer to encoded MP3 stream
                                                    mp3BufferSizeInBytes);    // number of valid octets in this stream

            if(retval<0)
            {
                qDebug()<<"lame_encode_buffer_float return -1";
                goto ERROR_EXIT;
            }
            qDebug()<<retval;
            retval=lame_encode_flush(gfp,mp3buffer,mp3BufferSizeInBytes);
            if(retval<0)
            {
                qDebug()<<"lame_encode_flush -1";
                goto ERROR_EXIT;
            }
            qDebug()<<retval;
            free(buffer_l);
            free(buffer_r);
            free(mp3buffer);
            buffer_l=NULL;
            buffer_r=NULL;
            mp3buffer=NULL;
        }
    }
    else
    {
        qDebug()<<"open failed ";
    }
ERROR_EXIT:
    free(buffer_l);
    free(buffer_r);
    free(mp3buffer);
    qDebug()<<sf_strerror(sndfile);
    sf_close(sndfile);
    lame_close(gfp);
}

void METhread::mp32wav(const QString& fileName)
{
    char* name=(OS_IS_WIN32?fileName.toLocal8Bit().data():
                       fileName.toUtf8().data());
    struct stat statbuf;
    int numOfByte;
    memset(&statbuf,0,sizeof(statbuf));
    int fd=open(name,O_RDONLY|O_BINARY);
    if(fd<0)
        return;
    if(fstat(fd, &statbuf)<0)
        return;

    unsigned char* fileBuffer=(unsigned char*)malloc(sizeof(unsigned char)*statbuf.st_size);
    numOfByte=read(fd,fileBuffer,statbuf.st_size);
     qDebug()<<"mp32wav after read";
    if(numOfByte>0)
    {
        decode(fileBuffer,statbuf.st_size);
    }
    qDebug()<<"mp32wav";
    free(fileBuffer);
    close(fd);
}
