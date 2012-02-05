#ifndef _Exceptions_h_
#define _Exceptions_h_

#include <qstring.h>
#include <QWave2/qwave2defs.h>

namespace QWave2 {

/// SoundFileOpenError is thrown when there is an error in openning an audio file.
        class  SoundFileOpenError
        {
        private:
                QString _msg;
        public:
        SoundFileOpenError(const QString& message)
            :_msg(message)
                {}

                /**
                   @return The error message explaining how this exception was thrown.
                */
                QString what()
                { return _msg; }
        };

/*
  class QWaveInvalidChannelError
  {
  private:
  QString _msg;
  public:
  QWaveInvalidChannelError(const QString& message)
  :_msg(message)
  {}

  QString what()
  { return _msg; }
  };
*/

/// AudioDeviceError is thrown when there is an error in opening the audio device.
        class  AudioDeviceError
        {
        private:
                QString _msg;
        public:
        AudioDeviceError(const QString& message)
            :_msg(message)
                {}

                /**
                   @return The error message explaining how this exception was thrown.
                */
                QString what()
                { return _msg; }
        };

/// SampleRateConverterError is thrown when there is an error in converting the sampleing rate of the audio file.
        class  SampleRateConverterError
        {
        private:
                QString _msg;
        public:
        SampleRateConverterError(const QString& message)
            :_msg(message)
                {}

                /**
                   @return The error message explaining how this exception was thrown.
                */
                QString what()
                { return _msg; }
        };


}

#endif
