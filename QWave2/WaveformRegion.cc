#include "QWave2/WaveformRegion.h"
#include "QWave2/Waveform.h"
#include <cmath>

namespace QWave2 {

    WaveformRegion::WaveformRegion(Waveform* wave,
                                   double beg,
                                   double dur)
        : QGraphicsRectItem(),
          _wave(wave),
          _beg(beg),
          _dur(dur)
    {
        setZValue(5);
        wave->getCanvas()->addItem(this);
        adjust();
    }

    WaveformRegion::~WaveformRegion()
    {
    }

    void
    WaveformRegion::adjust()
    {
        double pps = _wave->getPixelsPerSecond();
        int x = (int)nearbyint((_beg-_wave->getBeginSeconds())*pps);
        int w = (int)nearbyint(_dur*pps);
        if (x + w > _wave->getWidthPixels())
            w = _wave->getWidthPixels() - x + 1;
        if (x < 0) {
            w = w + x;
            x = -1;
        }
        setRect(x, 0, w, _wave->getHeightPixels());
    }

    void
    WaveformRegion::setRegion(const double& beg,
                              const double& dur)
    {
        _beg = beg;
        _dur = dur;
        adjust();
    }

    int
    WaveformRegion::type() const
    {
        return Waveform::Rtti_Region;
    }

}
