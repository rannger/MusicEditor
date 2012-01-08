#include "plot.h"
#include "AudioData.h"
class SimpleData: public QwtData
{
    // The x values depend on its index and the y values
    // can be calculated from the corresponding x value.
    // So we donŽt need to store the values.
    // Such an implementation is slower because every point
    // has to be recalculated for every replot, but it demonstrates how
    // QwtData can be used.

public:
    SimpleData(double(*y)(double), size_t size):
        d_size(size),
        d_y(y)
    {
    }

    virtual QwtData *copy() const
    {
        return new SimpleData(d_y, d_size);
    }

    virtual size_t size() const
    {
        return d_size;
    }

    virtual double x(size_t i) const
    {
        return 0.1 * i;
    }

    virtual double y(size_t i) const
    {
        return d_y(x(i));
    }
private:
    size_t d_size;
    double(*d_y)(double);
};

Plot::Plot()
{
    setTitle("A Simple QwtPlot Demonstration");
    insertLegend(new QwtLegend(), QwtPlot::RightLegend);
//    update();
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(0.0);
    mY->attach(this);
    plotCurve=NULL;
}

void Plot::update(const QVector<double> &data)
{

    // Insert new curves
    if(plotCurve)
        plotCurve->detach();
    delete plotCurve;

    this->replot();
    QwtPlotCurve *plotCurve = new QwtPlotCurve("");
#if QT_VERSION >= 0x040000
    plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
#endif
    plotCurve->setPen(QPen(Qt::blue));
    plotCurve->attach(this);

    // Create sin and cos data
//    plotCurve->setData(SimpleData(::cos, 100));
    plotCurve->setData(AudioData(data));
    qDebug()<<AudioData(data).size();
    this->replot();
//    cCos->setData(SimpleData(::cos, 100));

}
