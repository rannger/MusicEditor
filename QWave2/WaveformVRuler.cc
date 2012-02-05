#include "QWave2/Waveform.h"
#include "QWave2/WaveformVRuler.h"
#include "QWave2/Utils.h"
#include <QPaintEvent>
#include <stdio.h>
using namespace std;

namespace QWave2 {

    WaveformVRuler::WaveformVRuler(QWidget* parent):
        QWidget(parent),
        _pm(new QPixmap(size())),
        _wave(NULL)
    {
        setFixedWidth(30);
    }

    WaveformVRuler::~WaveformVRuler()
    {
        if (_pm) delete _pm;
    }

    void
    WaveformVRuler::connectToWaveform(Waveform* wave)
    {
        if (_wave != NULL)
            _wave->disconnect(this);

        _wave = wave;
        connect(_wave,SIGNAL(waveformWindowResized(void)),
                this,SLOT(redraw(void)));
    }

    void
    WaveformVRuler::paintEvent(QPaintEvent* e)
    {
        QPainter p(this);
        p.drawPixmap(e->rect(),*_pm,e->rect());
    }

    void
    WaveformVRuler::resizeEvent(QResizeEvent*)
    {
        if (_pm) delete _pm;
        _pm = new QPixmap(size());
        _pm->fill(palette().color(QPalette::Window));
        redraw();
    }

    void
    WaveformVRuler::redraw(void)
    {
        if (_wave == NULL) return;
        if (_pm->isNull()) return;

        _pm->fill(palette().color(QPalette::Window));
        QPainter p(_pm);
        QFont f = p.font();
        f.setPixelSize(8);
        p.setFont(f);
        sprintf(_strbuf, "%.2f", 1.0/_wave->getAmplitudeRatio());
        int w = width();
        int h = height();
        int w_5 = w-5;
        int w_4 = w-4;
        int w_1 = w-1;
        int h_1 = h-1;
        int h4 = h/4;
        int h2 = h/2;
        p.drawText(0, 0, w_5, 8, Qt::AlignRight|Qt::AlignVCenter, _strbuf);
        p.drawText(0, h2-4, w_5, 8, Qt::AlignRight|Qt::AlignVCenter,"0");
        p.drawLine(w_4, 0,    w_1, 0);
        p.drawLine(w_4, h4,   w_1, h4);
        p.drawLine(w_4, h2,   w_1, h2);
        p.drawLine(w_4, h4*3, w_1, h4*3);
        p.drawLine(w_4, h_1,  w_1, h_1);
        p.drawLine(w_1, 0,    w_1, h_1);
    }  


}
