#ifndef _Waveform_h_
#define _Waveform_h_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <qmutex.h>
//#include <sndfile.h>
#include <QWave2/SndFile.h>

namespace QWave2 {

class WaveformBar;
class WaveformRegion;

/// Waveform provides a drawing area on which waveform is drawn.
/**
   It also provides a QCanvas that can be used to overlay user defined
   graphics on top of the waveform.  This canvas can be obtained using
   the getCanvas method.  This canvas is used by QWave2 to draw
   cursors and marked regions.

   A typical usage of the Waveform class looks like this.
     
   <pre>
   SndFile sndfile("speech.wav");
   QVBox vbox;
   Waveform waveform1(&sndfile, 0, 12.3, 1.1, &vbox);
   Waveform waveform2(&sndfile, 1, 12.3, 1.1, &vbox);</pre>

   This code snipet loads a 2-channel sound file (speech.wav), creates
   a QVBox, add Waveforms for each channel to the QVBox.  Initially, the
   region [12.3,13.4] is drawn, and this fills the Waveforms.  Different
   region can be drawn later using the Waveform::display method.

   <pre>
   waveform1.display(13.4, 1.5);
   waveform2.display(13.4, 1.5);</pre>
 */
class  Waveform: public QGraphicsView
{
  Q_OBJECT

public:
  /**
     @param sndfile   Sound file to be associated.
     @param channel   The channel of the sound file to be associated.
     @param beg   Waveform canvas' start position in seconds.
     @param dur   Width of the waveform canvas in seconds.
     @param parent   Parent widget.

     The sndfile and channel parameters determine which sound file and
     channel of the sound file to be associated with this Waveform.

     The beg and dur parameters determine the position and interval of
     the viewing window of the
     Waveform.  By default, beg=0.0 and dur=60.0.  These values are logical
     because they don't change the physical size of the widget.

     If this Waveform is to be a child of other widget, for example QVBox,
     QGrid, etc., specify the parent using the parent parameter.
   */
  Waveform(SndFile* sndfile,
	   int channel,
	   double beg=0.0,
	   double dur=60.0,
	   QWidget *parent=NULL);
  ~Waveform();
  ;
  /**
     The Waveform class manages two types of QCanvasItems: WaveformBar and
     WaveformRegion.  RTTI (RunTime Type Information) is used to distinguish
     them at runtime.

     <pre>
     void doSomthingForItem(QCanvasItem* item)
     {
       switch (item->rtti()) {
       case Waveform::Rtti_Region:
         ...
         break;
       case Waveform::Rtti_Bar:
         ...
         break;
       default:
         ...
         break;
       }
     }</pre>

   */
  enum CanvasItemRTTI {
    /// RTTI of WaveformRegion
    Rtti_Region=10,
    /// RTTI of WaveformBar
    Rtti_Bar=11
  };

  /**
     @return The sound file associated with this Waveform.
   */
  SndFile* getSndFile() const;

  /**
     @return The channel of the sound file associated with this Waveform.
   */
  int getChannel() const;

  /**
     @return The amplitude ratio of the waveform. Amplitude ratio is the
     factor by which the waveform is zoomed-in vertically.
   */
  double getAmplitudeRatio() const;

  /**
     @return QPaintDevice on which the waveform is drawn.
   */
  QPaintDevice* getPaintDevice();

  /**
     @return QCanvas that is overlayed on top of the waveform.  This canvas
     can be used to place user defined graphics.
   */
  QGraphicsScene* getCanvas();

  /**
     @param beg   The logical position in seconds where the bar will be
     placed.
     @return   Newly created WaveformBar.

     Thid method creates a WaveformBar and places it on the canvas
     on the position specified
     by the beg parameter.  The pointer of the created WaveformBar is
     returned as a return value.

     WaveformBars registered with a Waveform 
     are managed, i.e. the user doesn't need to
     worry about resizing and moving them around when the waveform
     is scrolled and/or resized.

   */
  WaveformBar* addBar(const double& beg);

  /**
     @param beg   The logical position in seconds where the region will be
     placed.
     @param dur   The width of the region in seconds.
     @return   Newly created WaveformRegion

     Thid method creates a WaveformRegion with the width specified by
     the dur parameter and places it on the canvas on the position
     specified by the beg parameter.  The pointer of the created
     WaveformRegion is returned as a return value.

     WaveformRegions registered with a Waveform
     are managed, i.e. the user doesn't
     need to worry about resizing and moving them around when the waveform
     is scrolled and/or resized.
   */
  WaveformRegion* addRegion(const double& beg, const double& dur);

  /**
     @return   The start position of the drawing area in frames.
   */
  double getBeginFrames() const;

  /**
     @return   The witdth of the drawing area in frames.
   */
  double getWidthFrames() const;

  /**
     @return   The start position of the drawing area in seconds.
   */
  double getBeginSeconds() const;

  /**
     @return   The width of the drawing area in seconds.
   */
  double getWidthSeconds() const;

  /**
     @return   The start positon of the drawing area in pixels.
   */
  double getBeginPixels() const;

  /**
     @return   The width of the drawing area in pixels.
   */
  int getWidthPixels() const;

  /**
     @return   The height of the drwaing area in pixels.
   */
  int getHeightPixels() const;

  // just for convenience
  /**
     @return   The number of seconds in one pixel.
   */
  double getSecondsPerPixel() const;

  /**
     @return   The number of pixels in one second.
   */
  double getPixelsPerSecond() const;

  /**
     @return   The number of frames in one pixel.
   */
  double getFramesPerPixel() const;

  /**
     @return   The number of pixels in one frame.
   */
  double getPixelsPerFrame() const;

  /**
     @return   The number of seconds in one frame.
   */
  double getSecondsPerFrame() const;

  /**
     @return   The number of frames in one second.
   */
  double getFramesPerSecond() const;

  /**
     @param px   The pixel position relative to the drawing area.
     @return   The converted time position.
   */
  double px2time(const double& px) const;

  /**
     @param s   The time position.
     @return   The pixel position relative to the drawing area.
   */
  double time2px(const double& s) const;

  /**
     @param f   The frame position.
     @return   The pixel position relative to the drawing area.
   */
  double frm2px(const double& f) const;

  /**
     @param px   The pixel position relative to the drawing area.
     @return   The frame position.
   */
  double px2frm(const double& px) const;

  /**
     @param f   The frame postion.
     @return   The time positon.
   */
  double frm2time(const double& f) const;

  /**
     @param t   The time position.
     @return   The frame position.
   */
  double time2frm(const double& t) const;

public slots:
  /**
     @param beg   Start position of the drawing area in seconds.
     @param dur   Width of the drawing area in seconds.

     This method resets the position and interval of the viewing window,
     and the region of the waveform file specified by beg and dur will be
     drawn on the widget.  If dur is larger than 120 (2 minutes) or less
     than 0.00001, then this method will just return (nothing will happen).

     Note that this method doesn't change the physical geometry of
     the widget.
   */
  void display(double beg, double dur);
 
  /**
     @param beg   Start position of the drawing area in seconds.

     This method moves the position of the viewing window to beg.
     Because it leaves the duration of the waveform unchanged, this
     can be useful when scrolling the waveform.
   */
  void display(double beg);

  /**
     @param ratio   Amplitude ratio.  Amplitude ratio is the factor
     by which the waveform is zoomed-in vertically.
     @note This doesn't affect the volume of the playback of the sound file.
   */
  void setAmplitudeRatio(double ratio);

signals:
  /**
     @param beg   The new start position of the viewing window in seconds.
     @param dur   The width of the viewing window in seconds.

     This signal informs that the position and inverval of the viewing
     window.  The new start position is beg second and the width
     is dur seconds.
   */
  void waveformHorizontallyChanged(double beg, double dur);

  //void waveformVerticallyChanged(double amp);

  /**
     This signal informs that the Waveform widget has been resized.
     Note that it doesn't mean that the viewing window has changed.
   */
  void waveformWindowResized();

  /**
     @param beg   The position (in seconds) at the mouse button was pressed.

     Mouse button has been pressed at beg second.
   */
  void waveformMousePressed(Waveform* wave, double beg);

  /**
     @param beg   The position (in seconds) where the mouse movement was
     detected.

     Mouse movement has been detected at beg second.
   */
  void waveformMouseMoved(Waveform* wave, double beg);

  /**
     @param beg   The position (in seconds) where the mouse button was
     released.

     Mouse button has been released at beg second.
   */
  void waveformMouseReleased(Waveform* wave, double beg);

protected:
  void resizeEvent(QResizeEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

private:
  SndFile* _sndfile;
  int _samplerate;
  int _channel;
  double _beg;
  double _dur;
  int _width;
  int _height;
  double _spp;  // seconds per pixel
  double _pps;  // pixels per second
  double _amp;
  QMutex _display_mutex;

  QGraphicsScene _canvas;
  QPixmap* _waves[2];
  QGraphicsPixmapItem _pixmap;
  //QImage _waves[2];
  int _waveidx;

  void adjustCanvasItems();
  void flushWaveform();

};


}

#endif
