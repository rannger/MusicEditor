#ifndef _WaveformRegion_h_
#define _WaveformRegion_h_

#include <QGraphicsRectItem>
#include <QMutex>
//#include <sndfile.h>
#include <QWave2/SndFile.h>

namespace QWave2 {

class Waveform;

/// WaveformRegion is a rectangle whose height is the same as the Waveform's.
/**
   WaveformRegion is used by the QWave2 library to represent some region
   on the associated Waveform.  For example, when the user select a region
   on the waveform by clicking on it and dragging, a rectangle can be
   drawn to mark the selected region.
 */
class  WaveformRegion: public QGraphicsRectItem
{
public:
  /**
     Create a WaveformRegion on the given waveform, location and duration.
     The location means where the left side of the rectangle is located.
     Location and duration are both 0.0 by default.

     @param wave The waveform on which the rectangle will be drawn.
     @param beg The position where the left side of the rectangle will be
     located.
     @param dur The width of the rectangle in seconds.
   */
  WaveformRegion(Waveform* wave,
		 double beg=0.0,
		 double dur=0.0);
  ~WaveformRegion();

  /**
     This method can be called to adjust it's position and size to the
     changes made to the associated waveform.  For example, if the
     waveform is scrolled to the left or right, the region also needs to
     be moved accordingly.  Since this doesn't happen automatically, you
     have to use the adjust() method to make this happen.
   */
  void adjust();

  /**
     Set the position and size of the region by specifying where the
     region's left side should be positioned and what the width should
     be.

     @param beg The location of the rectangle's left side.
     @param dur The width of the rectangle in seconds.
   */
  void setRegion(const double& beg, const double& dur);

  /**
     Returns Waveform::Rtti_Region.  This value is used to distinguish
     between different QCanvasItems.

     @return Waveform::Rtti_Region
   */
  int type() const;

private:
  Waveform* _wave;
  double _beg, _dur;
};


}

#endif
