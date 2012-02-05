#include <qstring.h>
#include <cstdio>
#include "QWave2/Utils.h"

namespace QWave2 {

    QString
    time2str(double t, int e)
    {
        char const * sign = "";
        if (t < 0) {
            sign = "-";
            t = -t;
        }
        double shift = 1.0;
        double roundup = 0.5;
        for (int i=0; i<e; ++i) {
            shift *= 10.0;
            roundup /= 10.0;
        }
        t += roundup;
        int sec = (int)t;
        int msec = (int)((t-(double)sec)*shift);
        int min = sec / 60;
        int hour = min / 60;
        min %= 60;
        sec %= 60;
        char s[128];
        if (hour != 0)
            sprintf(s,"%s%d:%02d:%02d.",sign,hour,min,sec);
        else if (min != 0)
            sprintf(s,"%s%d:%02d.",sign,min,sec);
        else
            sprintf(s,"%s%d.",sign,sec);
        char f[16];
        sprintf(f,"%%0%dd",e);
        sprintf(&s[strlen(s)],f,msec);
        return QString(s);
    }

}
