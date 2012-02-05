#include "QWave2/Events.h"

namespace QWave2 {

    PlayerPositionEvent::PlayerPositionEvent(double t)
        : QEvent((QEvent::Type)PlayerPosition),
          _t(t)
    {
    }

    double
    PlayerPositionEvent::time() const
    {
        return _t;
    }

}
