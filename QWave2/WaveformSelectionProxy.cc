#include "QWave2/WaveformSelectionProxy.h"
#include "QWave2/Waveform.h"
#include "QWave2/WaveformRegion.h"

namespace QWave2 {

WaveformSelectionProxy::WaveformSelectionProxy(QObject* parent)
  : QObject(parent),
    _beg(0.0),
    _dur(0.0),
    _flexing(false),
    _focused(Qt::red),
    _unfocused(Qt::yellow),
    _focusedWaveform(NULL)
{
}


WaveformSelectionProxy::~WaveformSelectionProxy()
{
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.begin();
  for (; pos != _reg.end(); ++pos) {
    pos->first->disconnect(this);
    //delete pos->second;
  }
}

void
WaveformSelectionProxy::registerWaveform(Waveform* wave)
{
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.find(wave);
  if (pos == _reg.end()) {
    _reg[wave] = wave->addRegion(_beg,_dur);
    _reg[wave]->setPen(_unfocused);
    connect(wave, SIGNAL(waveformMousePressed(Waveform*,double)),
	    this, SLOT(beginSelection(Waveform*,double)));
    connect(wave, SIGNAL(waveformMouseMoved(Waveform*,double)),
	    this, SLOT(expandSelection(Waveform*,double)));
    connect(wave, SIGNAL(waveformMouseReleased(Waveform*,double)),
	    this, SLOT(freezeSelection(Waveform*,double)));
    connect(wave, SIGNAL(destroyed(QObject*)),
	    this, SLOT(waveformDestroyed(QObject*)));
  }
}

void
WaveformSelectionProxy::waveformDestroyed(QObject* obj)
{
  unregisterWaveform(static_cast<Waveform*>(obj));
}

void
WaveformSelectionProxy::unregisterWaveform(Waveform* wave)
{
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.find(wave);
  if (pos != _reg.end()) {
    pos->first->disconnect(this);
    this->disconnect(pos->first);
    _reg.erase(pos);
    if (_reg.size() == 0) {
      _beg = 0.0;
      _dur = 0.0;
      _flexing = false;
      _focusedWaveform = NULL;
    }
  }
}

void
WaveformSelectionProxy::setColorScheme(const QColor& focused, const QColor& unfocused)
{
  _focused = focused;
  _unfocused = unfocused;
}

double
WaveformSelectionProxy::getBeginSeconds()
{
  return _beg;
}

double
WaveformSelectionProxy::getWidthSeconds()
{
  return _dur;
}

Waveform*
WaveformSelectionProxy::getSelectedWaveform()
{
  return _focusedWaveform;
}

void
WaveformSelectionProxy::select(const double& beg, const double& dur, Waveform* wform)
{
  _beg = beg;
  _dur = dur;
  _focusedWaveform = wform;
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.begin();
  for (; pos != _reg.end(); ++pos) {
    if (pos->first == wform)
      pos->second->setPen(_focused);
    else
      pos->second->setPen(_unfocused);

    pos->second->setRegion(_beg, _dur);
    pos->first->getCanvas()->update();
  }
}

void
WaveformSelectionProxy::beginSelection(Waveform* wave, double beg)
{
  _pivot = _beg = beg;
  _dur = 0.0;
  _flexing = true;
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.begin();
  _focusedWaveform = NULL;
  for (; pos != _reg.end(); ++pos) {
    if (pos->first == wave) {
      pos->second->setPen(_focused);
      _focusedWaveform = pos->first;
    }
    else
      pos->second->setPen(_unfocused);
    pos->second->setRegion(_pivot, 0.0);
    pos->first->getCanvas()->update();
  }
  emit(waveformSelectionChanged(_beg,_dur,_focusedWaveform));
}

void
WaveformSelectionProxy::expandSelection(Waveform*, double beg)
{
  if (_flexing) {
    if (beg < _pivot) {
      _beg = beg;
      _dur = _pivot - beg;
    }
    else {
      _beg = _pivot;
      _dur = beg - _pivot;
    }
    map<Waveform*,WaveformRegion*>::iterator pos = _reg.begin();
    for (; pos != _reg.end(); ++pos) {
      /*
      if (pos->first->hasMouse())
	pos->second->setPen(_focused);
      else
	pos->second->setPen(_unfocused);
      */
      pos->second->setRegion(_beg, _dur);
      pos->first->getCanvas()->update();
    }

    emit(waveformSelectionChanged(_beg,_dur,_focusedWaveform));
  }
}

void
WaveformSelectionProxy::expandSelectionBegin(Waveform* wave, double beg)
{
  _flexing = true;
  _pivot = _beg + _dur;
  expandSelection(wave, beg);
}

void
WaveformSelectionProxy::expandSelectionEnd(Waveform* wave, double beg)
{
  _flexing = true;
  _pivot = _beg;
  expandSelection(wave, beg);
}

void
WaveformSelectionProxy::freezeSelection(Waveform*, double)
{
  _flexing = false;
  map<Waveform*,WaveformRegion*>::iterator pos = _reg.begin();
  for (; pos != _reg.end(); ++pos) {
    /*
    if (pos->first->hasMouse())
      pos->second->setPen(_focused);
    else
      pos->second->setPen(_unfocused);
    */
    pos->first->getCanvas()->update();
  }
}

}
