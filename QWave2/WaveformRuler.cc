#include "QWave2/Waveform.h"
#include "QWave2/WaveformRuler.h"
#include "QWave2/Utils.h"
#include <cmath>
#include <QPaintEvent>
#if defined(__GNUC__) && __GNUC__ < 3
#include <limits.h>
#else
#include <limits>
#endif

using namespace std;

static double _tmp1[34] = {
  36000.0, 18000.0, 7200.0, 3600.0, 1800.0,
  1200.0, 600.0, 300.0, 120.0,
  60.0, 30.0, 20.0, 10.0,
  5.0, 2.0, 1.0,
  0.50, 0.20, 0.10,
  0.05, 0.02, 0.01,
  0.005, 0.002, 0.001,
  0.0005, 0.0002, 0.0001,
  0.00005, 0.00002, 0.00001,
  0.000005, 0.000002, 0.000001};
static int _tmp2[34] = {
  2, 5, 2, 2, 3,
  2, 2, 5, 2,
  2, 2, 2, 2,
  5, 2, 2,
  5, 2, 2,
  5, 2, 2,
  5, 2, 2,
  5, 2, 2,
  5, 2, 2,
  5, 2, 2};


static int
ilog10(double x)
{
  double tmp = -log10(x);
  int exp = (int)tmp;
  if (tmp-(double)exp > 0.0001) ++exp;
  return exp;
}


namespace QWave2 {

WaveformRuler::WaveformRuler(bool attachToTop, QWidget* parent):
        QWidget(parent),
        _pm(new QPixmap(size())),
        _wave(NULL),
        _height(18),
        _textHeight(8),
        _beg(-9999999.0),
        _dur(-9999999.0)
{
  for (int i=0; i<25; ++i)
    _units[_tmp1[i]] = _tmp2[i];

  setFixedHeight(_height);
  if (attachToTop) {
    _textTop = 1;
    _bigTop = _height - 8 - 1;
    _smallTop = _height - 5 - 1;
    _lineTop = _height - 1;
  }
  else {
    _textTop = _height - _textHeight - 1;
    _bigTop = 8;
    _smallTop = 5;
    _lineTop = 0;
  }

}

WaveformRuler::~WaveformRuler()
{
    if (_pm) delete _pm;
}

void
WaveformRuler::connectToWaveform(Waveform* wave)
{
  if (_wave != NULL)
    _wave->disconnect(this);

  _wave = wave;
  connect(_wave,SIGNAL(waveformHorizontallyChanged(double,double)),
          this,SLOT(redraw(double,double)));
  connect(_wave,SIGNAL(waveformWindowResized(void)),
          this,SLOT(redraw(void)));
  connect(_wave,SIGNAL(destroyed(QObject*)),
	  this,SLOT(waveformDestroyed(QObject*)));

  redraw();
}

void
WaveformRuler::waveformDestroyed(QObject* obj)
{
  if (_wave) {
    _wave->disconnect(this);
    _wave = NULL;
  }
}

void
WaveformRuler::disconnectWaveform()
{
  if (_wave != NULL) {
    _wave->disconnect(this);
    _wave = NULL;
  }

  _pm->fill(palette().color(QPalette::Background));
}

void
WaveformRuler::paintEvent(QPaintEvent* e)
{
  //bitBlt(this,e->rect().topLeft(),&_pm,e->rect());
  QPainter p(this);
  p.drawPixmap(e->rect(),*_pm,e->rect());
}

void
WaveformRuler::resizeEvent(QResizeEvent* e)
{
  //_pm.resize(e->size());
    if (_pm) delete _pm;
    _pm = new QPixmap(e->size());
  _pm->fill(palette().color(QPalette::Background));
  redraw();
}

void
WaveformRuler::redraw(bool doUpdate)
{
  if (_wave == NULL) return;
  if (_pm->isNull()) return;

  _pm->fill(palette().color(QPalette::Background));
  // we need at least 50 pixels beteen major ticks
  double spp = _wave->getSecondsPerPixel();
  double pps = _wave->getPixelsPerSecond();
  map<double,int>::iterator unit = _units.upper_bound(50 * spp);
  if (unit == _units.end()) return;
  double major = unit->first;
  double minor = major / unit->second;
  double t0 = _wave->getBeginSeconds();
  double beg = floor(t0 / major) * major;
  double end = beg + _wave->getWidthSeconds() + major;

  int exp = ilog10(major);
  if (exp < 1) exp = 1;

  double t, t1;
  int x;

  QPainter p(_pm);
  QFont f = p.font();
  f.setPixelSize(8);
  p.setFont(f);

  for (t=beg; t<end; t+=major) {
    x = (int)trunc((t-t0) * pps);
    p.drawLine(x, _bigTop, x, _lineTop);
    p.drawText(x-25, _textTop, 50, 8,
               Qt::AlignHCenter|Qt::TextDontClip,
	       time2str(t,exp));
    for (t1=t+minor; t1<t+major-minor/2.0; t1+=minor) {
      x = (int)trunc((t1-t0) * pps);
      p.drawLine(x, _smallTop, x, _lineTop);
    }
  }
  p.drawLine(0,_lineTop,width()-1,_lineTop);
  if (doUpdate) update();
}  

void
WaveformRuler::redraw(double beg, double dur)
{
  if (beg == _beg and dur == _dur) return;
  _beg = beg;
  _dur = dur;
  redraw();
}

}
