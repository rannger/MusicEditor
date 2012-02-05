#ifndef _WaveformScrollBar_h_
#define _WaveformScrollBar_h_

#include <QScrollBar>
#include <QPainter>
#include <set>
#include <QWave2/qwave2defs.h>
using namespace std;

namespace QWave2 {

        class Waveform;

/// WaveformScrollBar is responsible for scrolling registered waveforms.
/**
   Registered waveforms are synchronized by WaveformScrollBar so that they
   always display the same span.

   WaveformScrollBar is also a receiver of the PlayerPositionEvent
   event.  When registered to a SndPlayerTicker, a green indicator is
   drawn on the scroll bar to indicate where the player is playing.
*/
        class  WaveformScrollBar: public QScrollBar
        {
                Q_OBJECT

                    public:
                WaveformScrollBar(QWidget* parent=0);
                virtual ~WaveformScrollBar();

                /**
                   @param wave Waveform to be registered.
     
                   Register a new waveform with the scrollbar.
                */
                void registerWaveform(Waveform* wave);

                /**
                   @param wave Waveform to be unregistered.

                   Unregister the given waveform.
                */
                void unregisterWaveform(Waveform* wave);

        signals:
                /**
                   This signal is emitted when the user moves the scrollbar using
                   the mouse.  The argument is the start time of the viewing
                   window.
                */
                void waveformScrollBarScrolled(double);

        protected:
                /**
                   This method is called whenever the range control value changes.
                */
                virtual void sliderChange(SliderChange);
                /**
                   Called when the widget is resized.  Updates parameters that
                   are used to calculate the 
                */
                virtual void resizeEvent(QResizeEvent*);
                /**
                   Called when repainting is required.  Redraws the green indicator.
                */
                virtual void paintEvent(QPaintEvent*);
                /**
                   This method processes PlayerPositionEvent to draw a green
                   indicator on the scroll bar.
                */
                virtual void customEvent(QEvent*);

                protected slots:
                void parameterUpdate(double, double);
                void moveWaveform();

        private:
                multiset<double> ends;
                double scrollUnit;

                int _width;
                int _arrow_width;
                double _pps;
                int _x0;
                int _shift;       // sometimes waveform starts from negative seconds
                double _beg, _dur;    // start time and duration of current 
                // or previous viewing window

                inline int _time2x(int f);
                inline int _real_width();

        };

}

#endif
