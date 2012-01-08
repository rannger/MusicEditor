#ifndef PLOT_H
#define PLOT_H
#include "qwt_headfile.h"
#include <stdint.h>

class Plot : public QwtPlot
{
public:
    Plot();
    void update(const QVector<uint8_t> &data);
private:
    QwtPlotCurve* plotCurve;
};

#endif // PLOT_H
