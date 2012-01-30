#ifndef _WaveformRuler_h_
#define _WaveformRuler_h_

#include <qwidget.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QWave2/qwave2defs.h>
#include <map>
using namespace std;

namespace QWave2 {

class Waveform;

/// WaveformRuler is a horizontal timescale widget.
/**
   
 */
class  WaveformRuler: public QWidget
{
  Q_OBJECT

public:
  /**
     @param attachToTop If this boolean flag is set to true, the ruler
     will have its baseline at the bottom of the widget with numbers
     on upper part of the widget.  It's false by default.
     @param parent Parent widget.
     @param name Widget name.
   */
  WaveformRuler(bool attachToTop=false, QWidget* parent=0);
  ~WaveformRuler();

  /**
     @param wave The waveform to which the ruler is attached.

     Associate the ruler to the given waveform.
   */
  void connectToWaveform(Waveform* wave);

  /**
     Cancel the current association with a waveform.
   */
  void disconnectWaveform();

public slots:
  /**
     Redraw the ruler.  The parameters a and b are ignored.  The
     reason for their existence is to enable direct connection from
     some signals that transfer 2 doubles.
   */
  void redraw(double a,double b); 
  void redraw(bool doUpdate=true);

protected:
  /**
     Redraw the ruler.
   */
  virtual void paintEvent(QPaintEvent* e);
  /**
     Redraw the ruler when it is resized.
   */
  virtual void resizeEvent(QResizeEvent* e);

private slots:
  // this gets called before _wave is destroyed
  void waveformDestroyed(QObject* obj=0);

private:
  map<double,int> _units;
  QPixmap* _pm;
  Waveform* _wave;
  int _height;
  int _textHeight;
  int _textTop;
  int _bigTop;
  int _smallTop;
  int _lineTop;
  double _beg;
  double _dur;

};

}

#endif
