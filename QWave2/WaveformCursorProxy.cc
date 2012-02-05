#include "QWave2/WaveformCursorProxy.h"
#include "QWave2/WaveformBar.h"
#include "QWave2/Waveform.h"
#include "QWave2/Events.h"

namespace QWave2 {

    WaveformCursorProxy::WaveformCursorProxy(QObject* parent)
        : QObject(parent),
          _t(0.0),
          _focused(Qt::red),
          _unfocused(Qt::yellow)
    {
    }

    WaveformCursorProxy::~WaveformCursorProxy()
    {
        map<Waveform*,WaveformBar*>::iterator pos = _waves.begin();
        for (; pos != _waves.end(); ++pos) {
            pos->first->disconnect(this);
            //delete pos->second;
        }
    }

    void
    WaveformCursorProxy::registerWaveform(Waveform* wave)
    {
        map<Waveform*,WaveformBar*>::iterator pos = _waves.find(wave);
        if (pos == _waves.end()) {
            _waves[wave] = wave->addBar(_t);
            _waves[wave]->setPen(_unfocused);
            connect(wave,SIGNAL(waveformMouseMoved(Waveform*,double)),
                    this,SLOT(updateCursorPosition(Waveform*,double)));
            connect(wave,SIGNAL(destroyed(QObject*)),
                    this,SLOT(waveformDestroyed(QObject*)));
        }
    }

    void
    WaveformCursorProxy::waveformDestroyed(QObject* obj)
    {
        unregisterWaveform(static_cast<Waveform*>(obj));
    }

    void
    WaveformCursorProxy::unregisterWaveform(Waveform* wave)
    {
        map<Waveform*,WaveformBar*>::iterator pos = _waves.find(wave);
        if (pos != _waves.end()) {
            pos->first->disconnect(this);
            _waves.erase(pos);
        }
    }

    double
    WaveformCursorProxy::getCursorPositionSeconds()
    {
        return _t;
    }

    void
    WaveformCursorProxy::updateCursorPosition(Waveform* wave, double beg)
    {
        map<Waveform*,WaveformBar*>::iterator pos = _waves.begin();
        for (; pos != _waves.end(); ++pos) {
            if (pos->first == wave)
                pos->second->setPen(_focused);
            else
                pos->second->setPen(_unfocused);
            pos->second->setX(beg);
            pos->first->getCanvas()->update();
        }
        _t = beg;
    }

    void
    WaveformCursorProxy::setColorScheme(const QColor& focused, const QColor& unfocused)
    {
        _focused = focused;
        _unfocused = unfocused;
    }

    void
    WaveformCursorProxy::customEvent(QEvent* e)
    {
        if (e->type() == (QEvent::Type)PlayerPosition) {
            map<Waveform*,WaveformBar*>::iterator pos = _waves.begin();
            for (; pos != _waves.end(); ++pos) {
                pos->second->setPen(QPen(Qt::green));
                pos->second->setX(((PlayerPositionEvent*)e)->time());
                pos->first->getCanvas()->update();
            }
        }
    }

}

