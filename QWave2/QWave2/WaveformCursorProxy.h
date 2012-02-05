#ifndef _WaveformCursorProxy_h_
#define _WaveformCursorProxy_h_

#include <QObject>
#include <QColor>
#include <map>
#include <QWave2/qwave2defs.h>
using namespace std;

namespace QWave2 {

        class Waveform;
        class WaveformBar;

/// WaveformCursorProxy manages waveform cursors on the registered waveforms.
/**
   A red vertical bar is drawn at the x position of the mouse on the waveform
   on which the mouse pointer is. This waveform is called focused waveform,
   and the red bar is called focused cursor.  Other registered waveforms are
   called unfocused waveforms and yellow vertical bars are drawn on them at the
   same x position as the focused bar.  These yellow bars are called unfocused
   cursors.

   There is another type of cursor: player cursor.  When the
   WaveformCursorProxy object is registered with a SndPlayerTicker object,
   this green vertical cursors are drawn to indicate where the SndPlayer
   is playing.  Player cursors are drawn on all waveforms currently registered.
  
   The color scheme of the focused/unfocused cursors can be changed with
   the setColorScheme method.  The cursor position can be obtained using the
   getCursorPositionSeconds method.
*/
        class  WaveformCursorProxy: public QObject
        {
                Q_OBJECT

                    public:
                WaveformCursorProxy(QObject* parent=0);
                ~WaveformCursorProxy();

                /**
                   @param wave Waveform to be registered.

                   Register the given waveform.
                */
                void registerWaveform(Waveform* wave);
                /**
                   @param wave Waveform to be unregistered.

                   Unregister the given waveform.
                */
                void unregisterWaveform(Waveform* wave);
                /**
                   @return Current cursor position.

                   Returns the current cursor position in seconds.
                */
                double getCursorPositionSeconds();

                public slots:
                /**
                   @param wave The waveform to be the focused waveform.
                   @param beg The new cursor position.

                   Locate the cursors at beg on the registered waveforms.  The wave
                   parameter can be NULL.  In that case, no waveforms will get the
                   focused cursor.
                */
                void updateCursorPosition(Waveform* wave, double beg);
                /**
                   @param focused Color of the focused cursor.
                   @param unfocused Color of the unfocused cursor.

                   Change the color scheme of the cursors.
                */
                void setColorScheme(const QColor& focused, const QColor& unfocused);

        protected:
                /**
                   Receive the PlayerPositionEvent event posted by SndPlayerTicker and
                   draw the player cursors.
                */
                void customEvent(QEvent*);

                private slots:
                void waveformDestroyed(QObject* obj=0);

        private:
                map<Waveform*,WaveformBar*> _waves;
                double _t;
                QColor _focused;
                QColor _unfocused;
        };

}

#endif
