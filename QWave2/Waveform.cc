#include "QWave2/Waveform.h"
#include "QWave2/WaveformRegion.h"
#include "QWave2/WaveformBar.h"
//#include <Q3ValueList>
#include <QList>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <cmath>
#include <QDebug>


namespace QWave2 {

    Waveform::Waveform(SndFile* sndfile,
		       int channel,
		       double beg,
		       double dur,
		       QWidget *parent)
	: QGraphicsView(parent),
	  _sndfile(sndfile),
	  _samplerate(sndfile->getSampleRate()),
	  _channel(channel),
	  _beg(beg),
	  _dur(dur),
	  _spp(100000.0),
	  _pps(0.00001),
	  _amp(1.0),
	  _canvas(this),
	  _waveidx(0)
    {
	_waves[0] = _waves[1] = 0;
	setScene(&_canvas);
	setFrameShape(NoFrame);
	_canvas.addItem(&_pixmap);
	//setMouseTracking(true);
	//viewport()->setMouseTracking(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setCacheMode(QGraphicsView::CacheNone);
    }

    Waveform::~Waveform()
    {
	if (!_waves[0]) delete _waves[0];
	if (!_waves[1]) delete _waves[1];
    }

    int
    Waveform::getChannel() const
    {
	return _channel;
    }

    double
    Waveform::getAmplitudeRatio() const
    {
	return _amp;
    }

    double
    Waveform::getBeginFrames() const
    {
        return _beg * this->getFramesPerSecond();
    }

    double
    Waveform::getWidthFrames() const
    {
        return this->_sndfile->getFrames();
    }

    double
    Waveform::getBeginSeconds() const
    {
	return _beg;
    }

    double
    Waveform::getWidthSeconds() const
    {
	return _dur;
    }

    double
    Waveform::getBeginPixels() const
    {
	return _pps * _beg;
    }

    int
    Waveform::getWidthPixels() const
    {
	return _width;
    }

    int
    Waveform::getHeightPixels() const
    {
	return _height;
    }

    QPaintDevice*
    Waveform::getPaintDevice()
    {
	return _waves[_waveidx];
    }

    double
    Waveform::getSecondsPerPixel() const
    {
	return _spp;
    }

    double
    Waveform::getPixelsPerSecond() const
    {
	return _pps;
    }

    double
    Waveform::getFramesPerPixel() const
    {
        return this->_sndfile->getFrames()/this->_width;
	return _spp * _samplerate;
    }

    double
    Waveform::getPixelsPerFrame() const
    {
//	return _pps / _samplerate;
        return _width/this->_sndfile->getFrames();
    }

    double
    Waveform::getSecondsPerFrame() const
    {
//	return 1.0 / _samplerate;
        return _dur/this->_sndfile->getFrames();

    }

    double
    Waveform::getFramesPerSecond() const
    {
        return this->_sndfile->getFrames()/_dur;
//	return (double)_samplerate;
    }

    double
    Waveform::px2time(const double& px) const
    {
        return this->getSecondsPerPixel()*px+_beg;
	return px * _spp + _beg;
    }

    double
    Waveform::time2px(const double& t) const
    {
        return this->getPixelsPerSecond()*(t-_beg);
	return _pps * (t - _beg);
    }

    double
    Waveform::frm2px(const double& f) const
    {
        return this->getPixelsPerFrame()*f;
	return (f / _samplerate - _beg ) * _pps;
    }

    double
    Waveform::px2frm(const double& px) const
    {
        return this->getFramesPerPixel()*px;
	return (px * _spp + _beg) * _samplerate;
    }

    double
    Waveform::frm2time(const double& f) const
    {
        return this->getSecondsPerFrame()*f;
	return f / _samplerate;
    }

    double
    Waveform::time2frm(const double& t) const
    {
        return getFramesPerSecond()*t;
	return t * _samplerate;
    }

    void
    Waveform::resizeEvent(QResizeEvent* e)
    {

	const QSize& s = e->size();

	_width = s.width() - 1;
	_height = s.height() - 1;
        qDebug("resize width:%d",_width);
	_canvas.setSceneRect(0,0,_width,_height);
	//_waves[_waveidx].resize(s);
	//_waves[!_waveidx].resize(s);
	if (!_waves[0]) delete _waves[0];
	if (!_waves[1]) delete _waves[1];
	_waves[0] = new QPixmap(_width, _height);
	_waves[1] = new QPixmap(_width, _height);

        _pps = (double)_width / _dur;
        _spp = (double)_dur / _width;

        _waves[_waveidx]->fill();
        _sndfile->drawWaveform(this,_channel,_beg, _dur);

	flushWaveform();
	adjustCanvasItems();
	emit(waveformWindowResized());

    }

    void
    Waveform::mousePressEvent(QMouseEvent* e)
    {
	emit(waveformMousePressed(this, _spp * e->x() + _beg));
    }

    void
    Waveform::mouseMoveEvent(QMouseEvent* e)
    {
	emit(waveformMouseMoved(this, _spp * e->x() + _beg));
    }

    void
    Waveform::mouseReleaseEvent(QMouseEvent* e)
    {
	emit(waveformMouseReleased(this, _spp * e->x() + _beg));
    }

    void
    Waveform::adjustCanvasItems()
    {
	QList<QGraphicsItem*> items = _canvas.items();
	for (int i=0; i < items.size(); ++i) {
	    switch (items[i]->type()) {
	    case Rtti_Region:
		static_cast<WaveformRegion*>(items[i])->adjust();
		items[i]->show();
		break;
	    case Rtti_Bar:
		static_cast<WaveformBar*>(items[i])->adjust();
		items[i]->show();
		break;
	    }
	}
    }

    void
    Waveform::flushWaveform()
    {
	_pixmap.setPixmap(*_waves[_waveidx]);
	//_canvas.setBackgroundPixmap(_waves[_waveidx]);
	_canvas.update();
    }

    void
    Waveform::display(double beg, double dur)
    {
	if (!_display_mutex.tryLock())
	    return;

	if ((beg == _beg and dur == _dur) or  // drawing the same thing
	    dur < 0.00001 or                  // duration too small
	    dur > 120.0)                      // duration is too large
	{
	    _display_mutex.unlock();
	    return;
	}

	if (dur != _dur or fabs(beg-_beg)>_dur or _pps/_samplerate > 0.25) {
	    _dur = dur;
	    _pps = (double)_width / _dur;
	    _spp = (double)_dur / _width;
	    _beg = trunc(beg*_pps)*_spp;
	    _waves[_waveidx]->fill();
	    _sndfile->drawWaveform(this,_channel,_beg, _dur+1.0/_samplerate);
	}
	else {
	    double d;
	    int dx;
	    QPixmap* src = _waves[_waveidx];
	    QPixmap* dst = _waves[!_waveidx];
	    _waveidx = !_waveidx;

	    // assume that _beg is already aligned to a pixel
	    dx = abs((int)nearbyint((_beg - beg)/_spp));
	    d = dx * _spp;

	    if (beg < _beg) {
		// scroll left = shift right = clicked "<-"
		//bitBlt(dst, dx,0, src, 0,0,_width-dx,_height, Qt::CopyROP, false);
		//bitBlt(dst, 0,0, dst, 0,0,dx,_height, Qt::NotOrROP, false);
		QPainter p;
		p.begin(dst);
		p.drawPixmap(dx,0, *src, 0,0,_width-dx,_height);
		//p.drawPixmap(0,0, *dst, 0,0,dx,_height);
		p.eraseRect(0,0,dx,_height);
		p.end();
		_beg -= d;
		_sndfile->drawWaveform(this,_channel,_beg, d);
	    }
	    else {
		// scroll right = shift left = clicked "->"
		//bitBlt(dst, 0,0, src, dx,0,_width-dx,_height, Qt::CopyROP, false);
		//bitBlt(dst, _width-dx,0, dst, _width-dx,0,dx,_height, Qt::NotOrROP, false);
		QPainter p;
		p.begin(dst);
		p.drawPixmap(0,0, *src, dx,0,_width-dx,_height);
		//p.drawPixmap(_width-dx,0, *dst, _width-dx,0,dx,_height);
		p.eraseRect(_width-dx,0,dx,_height);
		p.end();
		_beg += d;
		_sndfile->drawWaveform(this,_channel,_beg+(_width-dx)*_spp, d);
	    }

	}

	flushWaveform();
	adjustCanvasItems();
	//int id = rand();
	//qDebug() << "emit " << id << " " << _beg << " " << _dur;
        emit(waveformHorizontallyChanged(_beg,_dur/4));
	//qDebug() << "emit done " << id;
	_display_mutex.unlock();
    }

    void
    Waveform::display(double beg)
    {
	display(beg, _dur);
    }

    void
    Waveform::setAmplitudeRatio(double amp)
    {
	_amp = amp;
	_waves[_waveidx]->fill();
	_sndfile->drawWaveform(this,_channel,_beg, _dur);
	flushWaveform();
	adjustCanvasItems();
    }


    WaveformBar*
    Waveform::addBar(const double& beg)
    {
	WaveformBar* c = new WaveformBar(this, beg);
	c->show();
	return c;
    }

    WaveformRegion*
    Waveform::addRegion(const double& beg, const double& dur)
    {
	WaveformRegion* r = new WaveformRegion(this, beg, dur);
	r->show();
	return r;
    }

    QGraphicsScene*
    Waveform::getCanvas()
    {
	return &_canvas;
    }

    SndFile*
    Waveform::getSndFile() const
    {
	return _sndfile;
    }

}
