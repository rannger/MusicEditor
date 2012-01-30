#include "QWavePlayerSunAudio.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <stropts.h>
#include <sys/conf.h>

const char* QWavePlayerSunAudio::device = "/dev/audio";

QWavePlayerSunAudio::~QWavePlayerSunAudio()
{
  closeDevice();
}

void
QWavePlayerSunAudio::openDevice(int* channels, int* samplerate)
{
  /* open audio device */
  if ((fd = open(device,O_WRONLY,0)) == -1) {
    perror(device);
    throw QWaveAudioDeviceError(string(device)+": "+strerror(errno));
  }
  fcntl(fd, F_SETFL, O_NONBLOCK);   // this causes prompt responses

  /* set device format */
  AUDIO_INITINFO(&audio_info);

  audio_info.play.sample_rate = *samplerate;
  audio_info.play.channels = *channels;
  audio_info.play.precision = 16;
  audio_info.play.encoding = AUDIO_ENCODING_LINEAR;
  audio_info.play.port = AUDIO_HEADPHONE;

  if (ioctl(fd,AUDIO_SETINFO,&audio_info) == -1) {
    perror("AUDIO_SETINFO");
    throw QWaveAudioDeviceError(string("AUDIO_SETINFO: ")+strerror(errno));
  }

  *samplerate = audio_info.play.sample_rate;
  *channels = audio_info.play.channels;
  frame_size = audio_info.play.precision / 8 * *channels;
}

void
QWavePlayerSunAudio::closeDevice()
{
  close(fd);
}

unsigned
QWavePlayerSunAudio::getBufferSize()
{
  return audio_info.play.buffer_size / frame_size;
}

unsigned
QWavePlayerSunAudio::bytesPlayed()
{
  if (ioctl(fd, AUDIO_GETINFO, &audio_info) == -1) {
    perror("AUDIO_GETINFO");
    throw QWaveAudioDeviceError(string("AUDIO_GETINFO: ")+strerror(errno));
  }
  return (unsigned) audio_info.play.samples * frame_size;
}

void
QWavePlayerSunAudio::stopDevice()
{
  audio_info.play.pause = 1;
  if (ioctl(fd, AUDIO_SETINFO, &audio_info) == -1) {
    perror("AUDIO_SETINFO");
    throw QWaveAudioDeviceError(string("AUDIO_SETINFO: ")+strerror(errno));
  }
  if (ioctl(fd, I_FLUSH, FLUSHW) == -1) {
    perror("I_FULSH");
  }
}

int
QWavePlayerSunAudio::writeDevice(short* buf, int n)
{
  if (audio_info.play.pause) {
    audio_info.play.pause = 0;
    if (ioctl(fd, AUDIO_SETINFO, &audio_info) == -1) {
      perror("AUDIO_SETINFO");
      throw QWaveAudioDeviceError(string("AUDIO_SETINFO: ")+strerror(errno));
    }
  }
  return write(fd, buf, n);
}
