#ifndef _TimeLabel_h_
#define _TimeLabel_h_

#include <QLabel>
#include <QWave2/qwave2defs.h>
namespace QWave2 {

/// TimeLabel is a QLable that can display time in hh:mm:ss.ssss format.
/**
   TimeLabel is also a receiver of PlayerPositionEvent.  Therefore, if it
   is registered with SndPlayerTicker, it displayes the position of the
   player cursor in real-time.
*/
        class  TimeLabel: public QLabel
        {
                Q_OBJECT

                    public:
                TimeLabel(QWidget* parent=0);
                ~TimeLabel();

                public slots:
                /**
                   @param t The time to be displayed on the label.
                */
                void setTime(double t);

        protected:
                /**
                   @param e The pointer to a PlayerPositionEvent instance.
                */ 
                void customEvent(QEvent* e);
        };

}

#endif
