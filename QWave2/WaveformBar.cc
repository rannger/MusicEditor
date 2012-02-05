#include "QWave2/WaveformBar.h"
#include "QWave2/Waveform.h"
#include <cmath>

namespace QWave2 {

    WaveformBar::WaveformBar(Waveform* wave, double beg)
        : QGraphicsLineItem(),
          _wave(wave),
          _beg(beg)
    {
        setZValue(5);
        wave->getCanvas()->addItem(this);
    }

    WaveformBar::~WaveformBar()
    {
    }

    void
    WaveformBar::adjust()
    {
        int x = (int)nearbyint((_beg-_wave->getBeginSeconds())*_wave->getPixelsPerSecond());
        setLine(x,0,x,_wave->getHeightPixels()-1);
    }

    void
    WaveformBar::setX(const double& beg)
    {
        _beg = beg;
        adjust();
    }

    int
    WaveformBar::type() const
    {
        return Waveform::Rtti_Bar;
    }

    double
    WaveformBar::getBeginSeconds() const
    {
        return _beg;
    }

}

