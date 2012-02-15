#ifndef _SndFile_h_
#define _SndFile_h_

#include <cstddef>
#include <qpainter.h>
//#include <sndfile.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <QWave2/qwave2defs.h>

using namespace std;
class MEAudioDecoder;
class MEAuidoEncoder;

namespace QWave2 {

        class Waveform;

/// SndFile represents a sound file.
/**
   It is designed to be an efficient "waveform drawer" for the
   Waveform class rather than to be used to access samples in the
   sound file.  Therefore, the name of this class is somewhat
   misleading because you cannot access any samples of the sound file
   through this class.
   
   <pre>
   SndFile sndfile("speech.wav");
   Waveform waveform(&sndfile, 0);  // waveform for the first channel (0) 
                                    // of the speech.wav file</pre>

                                    QWave2 uses the libsndfile library (http://...) to access the sound
                                    file.  Thus, QWave2 supports whatever sound file format libsndfile
                                    supports.

                                    For faster access of audio samples, this class implements a cache
                                    with round-robin paging.  Each page of the cache amounts to 1
                                    second of sample frames.  The cacheSize parameter of the
                                    constructor determines the total number of pages in the cache and
                                    it defaults to 120.  It's about 4 MB if you are loading a
                                    two-channel PCM file with 16-bit samples sampled at 8 KHz.
                                    Although 4 MB is not a small amount of memory, it will bring
                                    considerable speed-ups in some situations, for example, when the
                                    waveform is scrolled continuously and contiguously.

                                    If SndFile is not used for waveform display, i.e. if it
                                    is not used with Waveform or, more specifically, if
                                    SndFile::drawWaveform is not called at all in the program, the
                                    cache is not used at all.  In this case, the cacheSize parameter
                                    can be set to 0 to save some memory.

                                    <pre>
                                    PLAYERIMPLEMENTATION player(2, 8000);
                                    SndFile sndfile("music.wav", 0);
                                    player.addSndFile(&sndfile);
                                    player.play(0.0, sndfile.getLengthSeconds());</pre>

*/
        class  SndFile
        {
        public:
                /**
                   @param filename   Sound file to load.  Any file format that the
                   libsndfile library supports is supported.
                   @param cacheSize   The number of 1-second cache pages to be created
                   in the cache.  Set this to 0 if your application doesn't use the
                   Waveform class or call the SndFile::drawWaveform method.
                   Otherwise, it's rarely necessary to change the default value (120).
                */
                SndFile(char const * filename, int cacheSize=MAXCACHEPAGES);
                SndFile(MEAudioDecoder* aDecoder,int numCPages=MAXCACHEPAGES);
                MEAudioDecoder* getDecoder(){return decoder;};
                virtual ~SndFile();
                QVector< short > data;
                /**
                   @param waveform   A Waveform object whose drawing area will be painted
                   with the waveform of the region specified by the channel, beg and dur
                   parameters below.
                   @param channel   The channel of the region to be drawn.
                   @param beg   The start time of the region to be drawn.
                   @param dur   The duration of the region to be drawn.

                   If beg < 0.0, it will be reset to 0.0.  If beg+dur exceeds the
                   length of the sound file, dur will be reset so that beg+dur equals
                   to the length of the sound file.  If dur is larger than the cache size
                   (120 seconds by default), it will be reset to the cache size.

                   Where the waveform is drawn is determined by the geometry of the
                   the Waveform.  This method will try to draw
                   the waveform on the drawing area of the Waveform, even though the
                   given region is outside of the area.
                */
                virtual void
                    drawWaveform(Waveform* waveform,
                        const int& channel,
                        const double& beg,
                        const double& dur);

                /**
                   @return The number of channels in the sound file.
                */
                virtual int
                    getChannels();

                /**
                   @return The sampling rate of the sound file.
                */
                virtual int
                    getSampleRate();

                /**
                   @return The length of the sound file in seconds.
                */
                virtual double
                    getLengthSeconds();

                unsigned long long getFrames();

                /**
                   @return The sound file name.  This is the same string as the one that
                   is given as the filename parameter of the constructor.
                */

                virtual char const*
                    getFileName();
                int lengthSeconds;
        protected:
                /**
                   Creates a dummy SndFile.
                */
                SndFile();

        private:
                string _filename;

//  SNDFILE* _sndfile;
//  SF_INFO _sfinfo;
                MEAudioDecoder* decoder;
  

                size_t _numCPages;
                short** _cache;
                vector<int> _unusedCPages;    // unused cache pages
                map<int,int> _index;          // real page -> cache page
                list<int> _heap;              // rpages ordered by read time

                int _loadPage(int k);
        };

}

#endif
