#include "QWave2/Utils.h"
#include "QWave2/Events.h"
#include "QWave2/TimeLabel.h"

namespace QWave2 {

TimeLabel::TimeLabel(QWidget* parent)
  : QLabel(parent)
{
  QFont f;
  f.setStyleHint(QFont::TypeWriter);
  f.setFixedPitch(true);
  setFont(f);
}

TimeLabel::~TimeLabel()
{
}

void
TimeLabel::setTime(double f)
{
  setText(time2str(f,4));
}

void
TimeLabel::customEvent(QEvent* e)
{
  if (e->type() == (QEvent::Type)PlayerPosition)
    setText(time2str(((PlayerPositionEvent*)e)->time(),4));
}

}
