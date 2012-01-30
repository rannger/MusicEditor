#ifndef _WaveformBar_h_
#define _WaveformBar_h_

#include <QGraphicsLineItem>
#include <QMutex>
//#include <sndfile.h>
#include <QWave2/SndFile.h>

namespace QWave2 {

class Waveform;

/// WaveformBar is a vertical line whose height is the same as the Waveform's on which it is drawn.
/**
   WaveformBar is used by the QWave2 library to represent mouse and
   playback cursors on the associated Waveform, but the usage is not
   limitted to those cases.  For example, you can use WaveformBar to mark
   some spot on the waveform.
 */
class  WaveformBar: public QGraphicsLineItem
{
public:
  /**
     Create a WaveformBar on the given waveform and location.
     The WaveformBar is located at 0.0 second by default.

     @param wave The waveform on which the bar will be drawn.
     @param beg Where to place the bar.
   */
  WaveformBar(Waveform* wave, double beg=0.0);
  ~WaveformBar();

  /**
     This method can be called to adjust it's position to the changes made
     to the associated waveform.  For example, if the waveform is scrolled
     to the left or right, the bar also needs to be moved accordingly.
     Since this doesn't happen automatically, you have to use the adjust()
     method to make this happen.
   */
  void adjust();

  /**
     Place the bar at beg at the given location.

     @param beg Location (in seconds) at which the bar will be placed.
   */
  void setX(const double& beg);

  /**
     Returns Waveform::Rtti_Bar.  This value is used to distinguish
     between different QCanvasItems.

     @return Waveform::Rtti_Bar
   */
  int type() const;

  /**
     Returns the position of the bar.

     @return The position of the bar in seconds.
   */
  double getBeginSeconds() const;

private:
  Waveform* _wave;
  double _beg;
};


}

#endif
