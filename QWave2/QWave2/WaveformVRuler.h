#ifndef _WaveformVRuler_h_
#define _WaveformVRuler_h_

#include <qpixmap.h>
#include <qcheckbox.h>
#include <QWave2/qwave2defs.h>

namespace QWave2 {

        class Waveform;

/// WaveformVRuler is a simple scale for displaying the amplitude of the associated waveform.
/**
   
 */
        class  WaveformVRuler: public QWidget
        {
                Q_OBJECT

                    public:
                /**
                   @param parent Parent widget.
                   @param name Widget name.
                */
                WaveformVRuler(QWidget* parent=0);
                ~WaveformVRuler();

                /**
                   @param wave The waveform to which the ruler will be attached.

                   Associated the ruler with the given waveform.
                */
                void connectToWaveform(Waveform* wave);

                public slots:
                /**
                   Redraw the ruler.
                */
                void redraw(void);
                //void setMutt(bool);

        protected:
                /**
                   This method is called when it's necessary to redraw the ruler.
                */
                virtual void paintEvent(QPaintEvent* e);
                /**
                   Called when the widget is resized to redraw the ruler.
                */
                virtual void resizeEvent(QResizeEvent* e);

        private:
                QPixmap* _pm;
                Waveform* _wave;
                char _strbuf[16];
                QCheckBox* _mutt;
        };

}

#endif
