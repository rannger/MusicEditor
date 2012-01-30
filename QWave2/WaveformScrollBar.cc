#include "QWave2/WaveformScrollBar.h"
#include "QWave2/Waveform.h"
#include "QWave2/Events.h"
#include <QStyleOption>
#include <QResizeEvent>
#include <cmath>

namespace QWave2 {

WaveformScrollBar::WaveformScrollBar(QWidget* parent)
  : QScrollBar(parent),
    _shift(0),
    _beg(0.0),
    _dur(0.0)
{
  setFocusPolicy(Qt::NoFocus);
  setOrientation(Qt::Horizontal);

  setRange(0,0);
  setSingleStep(1);
  setPageStep(10);
  
  QStyleOptionSlider option1;
  option1.initFrom(this);
    _arrow_width = style()->subControlRect(
            QStyle::CC_ScrollBar,
            &option1,
            QStyle::SC_ScrollBarGroove,
            this).left();
    _x0 = _arrow_width;

  connect(this,SIGNAL(sliderReleased()),
	  this,SLOT(moveWaveform()));
}

WaveformScrollBar::~WaveformScrollBar()
{
}

void
WaveformScrollBar::registerWaveform(Waveform* wave)
{
  if (ends.size() == 0) {
    _beg = 0.0;
    _dur = wave->getWidthSeconds();
    _shift = 0;
    scrollUnit = wave->getWidthSeconds() / 10.0;
  }

  ends.insert(wave->getSndFile()->getLengthSeconds());
  double e = *ends.rbegin();
  int max = static_cast<int>(nearbyint(e / scrollUnit)) - 10 + _shift;
  if (max < 0) max = 0;
  setMaximum(max);
  wave->display(_beg, _dur);
  _pps = static_cast<double>(_width) / (e + _shift * scrollUnit);

  connect(wave,SIGNAL(waveformHorizontallyChanged(double,double)),
          this,SLOT(parameterUpdate(double,double)));
  connect(this,SIGNAL(waveformScrollBarScrolled(double)),
	  wave,SLOT(display(double)));
}

void
WaveformScrollBar::unregisterWaveform(Waveform* wave)
{
  wave->disconnect(this);
  this->disconnect(wave);

  ends.erase(wave->getSndFile()->getLengthSeconds());

  double e = (ends.size()==0) ? 0.0 : *ends.rbegin();
  int max = (int)nearbyint(e / scrollUnit) - 10 + _shift;
  if (max < 0) max = 0;
  setMaximum(max);

  _pps = static_cast<double>(_width) / (e+_shift*scrollUnit);
}

void
WaveformScrollBar::sliderChange(SliderChange c)
{
  QScrollBar::sliderChange(c);
  if (c == SliderValueChange) 
    emit(waveformScrollBarScrolled(scrollUnit * (value()-_shift)));
}

void
WaveformScrollBar::resizeEvent(QResizeEvent* e)
{
    QScrollBar::resizeEvent(e);

    QStyleOptionSlider option2;
    option2.initFrom(this);
    _width = style()->subControlRect(
            QStyle::CC_ScrollBar,
            &option2,
            QStyle::SC_ScrollBarGroove,
            this).width();

    if (ends.size() > 0)
        _pps = static_cast<double>(_width) / (*ends.rbegin()+_shift*scrollUnit);
    else
        _pps = 0.0;
}

void
WaveformScrollBar::paintEvent(QPaintEvent* e)
{
    QScrollBar::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::green);
    p.drawLine(_x0, 4, _x0, height()-5);
}

void
WaveformScrollBar::customEvent(QEvent* e)
{
  if (e->type() == (QEvent::Type)PlayerPosition) {
    double t =
      static_cast<double>(_shift) * scrollUnit +
      static_cast<PlayerPositionEvent*>(e)->time();
    int x = _arrow_width + static_cast<int>(t) *_pps;
    if (x != _x0) {
      //update(QRect(_x0,0,1,height()));
        update();
      _x0 = x;
    }
  }
}

void
WaveformScrollBar::moveWaveform()
{
  emit(waveformScrollBarScrolled(scrollUnit * (value()-_shift)));
}

void
WaveformScrollBar::parameterUpdate(double beg, double dur)
{
  if (ends.size() == 0) return;

  double e = *ends.rbegin();
  scrollUnit = dur / 10.0;
  _shift = (beg<0) ? -(int)nearbyint(beg/scrollUnit) : 0;

  _beg = beg;
  _dur = dur;
  _pps = (double)_width / (e + _shift * scrollUnit);
  int max = (int)nearbyint(e / scrollUnit) - 10 + _shift;
  int val = (int)nearbyint(beg / scrollUnit)+_shift;
  if (val > max) max = val;
  if (max > maximum())
    setMaximum(max+1);
  //QScrollBar::directSetValue(val);
  setSliderPosition(val);
  setMaximum(max);
  QScrollBar::sliderChange(SliderValueChange);
}

}
