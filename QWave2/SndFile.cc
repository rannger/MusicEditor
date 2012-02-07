#include "QWave2/SndFile.h"
#include "QWave2/Waveform.h"
#include "QWave2/Exceptions.h"
#include <limits.h>
#include <cmath>
#include "meaudiodecoder.h"
#include "meauidoencoder.h"

namespace QWave2 {

    SndFile::SndFile(char const * filename, int numCPages)
	: _filename(filename),
	  _numCPages(numCPages<=0 ? 120: numCPages)
    {
	decoder=new MEAudioDecoder();
	if(decoder->initWithFile(QString(filename))<0)
	{
	    throw SoundFileOpenError(QString("can't open '")+filename+"'");
	}
	else
	{
	    int channels=decoder->getChannels();
	    int samplerate=decoder->getSampleRate();
	    _cache = new short*[_numCPages];
	    for (size_t i=0; i<_numCPages; ++i) {
		_cache[i] = new short[channels*samplerate];
		_unusedCPages.push_back(i);
	    }
	}
    }


    SndFile::SndFile(MEAudioDecoder* aDecoder,int numCPages)
	:_numCPages(numCPages<=0 ? 120: numCPages)
    {
        _numCPages<<=3;
	this->decoder=static_cast<MEAudioDecoder*>(aDecoder->retain());
	int channels=decoder->getChannels();
	int samplerate=decoder->getSampleRate();
	_cache = new short*[_numCPages];
	for (size_t i=0; i<_numCPages; ++i) {
	    _cache[i] = new short[channels*samplerate];
	    _unusedCPages.push_back(i);
	}

    }

    SndFile::SndFile()
    {
	decoder = 0;
    }

    SndFile::~SndFile()
    {
	if (!_filename.empty()) {
	    for (size_t i=0; i<_numCPages; ++i)
		delete[] _cache[i];
	    delete[] _cache;
	}
	decoder->release();
    }

    void
    SndFile::drawWaveform(Waveform* wave,
			  const int& ch,
			  const double& beg,
			  const double& dur)
    {
	if (wave->getPaintDevice()->height() == 0 ||
	    wave->getPaintDevice()->width() == 0)
	    return;
	int samplerate=this->getSampleRate();
	int channels=this->getChannels();

	unsigned long long frames=getFrames();
	int s = (int)nearbyint(beg * samplerate);     // first sample
        int e = (int)nearbyint(data.count()); // sample limit

	if (ch < 0 ||
	    ch >= channels ||
	    e <= 0 ||
	    s >= frames)
	    return;
        int s1 = (s < 0) ? 0 : s;
        int e1 = /*(e > frames) ? frames :*/ e;

	if (s1 >= e1)
	    return;

        int k1 = s1 / samplerate;         // first page

        int k2 = (int)ceil((double)e1/samplerate); // page limit
	if (k2 - k1 > (int) _numCPages) {
	    k2 = k1 + _numCPages;
	    e1 = k2 * samplerate;
	}

	int k, i;
	int m = k2-k1;    // number of pages we need
#ifdef _MSC_VER
	int cpages[MAXCACHEPAGES];
	int starts[MAXCACHEPAGES];
	int ends[MAXCACHEPAGES];
#else
	int cpages[m];
	int starts[m];    // index into frames within a cpage
	int ends[m];      // index into frames wrt the whole signal
#endif
	int upage;
	list<int>::iterator pos;
	long t=0;
	for (i=0, k=k1; k<k2; ++i, ++k) {
	    if (_index.find(k)==_index.end()) {
		// cache miss!

		// find a cache page to load page k
		if (_index.size() >= _numCPages) {
		    // cache is full; an old cpage should be gone
		    pos = _heap.begin();
		    while (*pos>=k1 && *pos<k2) ++pos;
		    upage = _index[*pos];
		    _index.erase(*pos);
		    _heap.erase(pos);
		}
		else {
		    upage = _unusedCPages.back();
		    _unusedCPages.pop_back();
		}

		// load page k
                if(t<data.count())
                {
                    const short* sdata=data.constData();
                    qDebug()<<"total:"<<data.count();
                    memcpy(_cache[upage],&sdata[k*samplerate],samplerate);
                    qDebug()<<"now:"<<(t+=samplerate);
                }

		_index[k] = upage;
		_heap.push_back(k);
	    }
	    else {
		upage = _index[k];
	    }

	    starts[i] = 0;
	    ends[i] = (k+1) * samplerate;
	    cpages[i] = upage;
	}

	starts[0] = s1 % samplerate;
	ends[m-1] = e1;

	// draw
	int f = s1;
        int _x=0;
        short *p = _cache[cpages[0]] + starts[0]*channels + ch;
	QPainter painter(wave->getPaintDevice());
	double r = wave->getPixelsPerFrame();
	const double h = wave->getAmplitudeRatio() * wave->getHeightPixels() / 2.0 / SHRT_MAX;
	const int center = wave->getHeightPixels() / 2;

	double pps = wave->getPixelsPerSecond();
	double spp = wave->getSecondsPerPixel();
	double t0 = wave->getBeginSeconds();

//  qDebug("%f", r);
	if (r<1.0) {
	    int x;
	    if (s != s1)
		x = (int)nearbyint((s1 / samplerate - t0) * pps);
	    else
		x = (int)nearbyint((beg - t0) / spp);

	    double t1 = (x+1) * spp + t0;
	    int f1 = (int)nearbyint(t1 * samplerate);
	    short min, max, y0=0;
	    bool new_pixel = false;
	    min = max = *p;

	    for (k=0; k<m; ++k) {
		p = _cache[cpages[k]] + starts[k]*channels + ch;
		while (f1 <= ends[k]) {
		    if (new_pixel) {
			new_pixel = false;
			if (*p < min || *p > max)
			{
			    painter.drawLine(x,(int)nearbyint(center-h*y0),x,(int)nearbyint(center-h*(*p)));
			}
			min = max = *p;
		    }
                    for (; f<f1; ++f, p++) {
			if (min > *p)
			    min = *p;
                        if (max < *p)
			    max = *p;
		    }
		    // draw line here!
                    painter.drawLine(x,(int)(center-h*min),x,(int)(center-h*max));
                    if(max!=min)
                        ++x;
		    new_pixel = true;
		    t1 += spp;
		    f1 = (int)nearbyint(t1 * samplerate);
		    y0 = *(p-channels);
		} // end of while
		if (f < ends[k]) {
		    new_pixel = false;
                    if (*p < min || *p > max)
		    {
			painter.drawLine(x,(int)nearbyint(center-h*y0),x,(int)nearbyint(center-h*(*p)));
                        x++;
		    }
		    min = max = *p;
                    for (; f<ends[k]; ++f, p++) {
			if (min > *p)
			    min = *p;
                        if (max < *p)
			    max = *p;
		    }
		} // end of if
	    }   // end of outermost for
	    if (!new_pixel)
	    {
		painter.drawLine(x,(int)nearbyint(center-h*min),x,(int)nearbyint(center-h*max));
                x++;
	    }
	}
	else {
	    //double x0 = wave->getBeginPixels();
	    double x1;
	    int x, y0, y;
	    y0 = center - (int)(*p * h);
	    for (k=0; k<m; ++k) {
		p = _cache[cpages[k]] + starts[k]*channels + ch;
		for (; f<ends[k]; ++f, p+=channels) {
		    x1 = ((double)f/samplerate - t0) * pps;
		    x = (int)trunc(x1);
		    y = center - (int)nearbyint(*p * h);
		    painter.drawLine(x,y0,x,y);
                    x++;
		    qDebug()<<__FILE__<<","<<__LINE__<<x;
		    painter.drawLine(x,y,(int)trunc(x1+r),y);
		    qDebug()<<__FILE__<<","<<__LINE__<<x;
		    y0 = y;
		}
	    }
	}

    }

    int
    SndFile::getChannels()
    {
	int retval=decoder->getChannels();
	return retval;
//  return channels;
    }

    int
    SndFile::getSampleRate()
    {
	int retval=decoder->getSampleRate();
	return retval;
//  return samplerate;
    }

    unsigned long long
    SndFile::getFrames()
    {
	unsigned long long frames=decoder->getNumberOfFrame();

	return frames;
    }

    double
    SndFile::getLengthSeconds()
    {
	int frames=0;
	int samplerate=0;
	return (double)frames/samplerate;
    }

    char const*
    SndFile::getFileName()
    {
	return _filename.c_str();
    }

}

