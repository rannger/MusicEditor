/**************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/
#include "plot.h"
#include "AudioData.h"
#include "mainwindow.h"
#include <assert.h>



Plot::Plot(QWidget *parent)
    :QwtPlot(parent)
    ,isPainted(false)
{
//    setTitle("A Simple QwtPlot Demonstration");
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

    plotCurve->setData(AudioData(data));
    qDebug()<<AudioData(data).size();
    this->replot();
    isPainted=true;
}

void Plot::finish()
{
    qDebug()<<"finish";
}

void Plot::showCurve(int num)
{
    this->clear();
    MainWindow* mainWindow=(MainWindow*)parent();
    assert(mainWindow);
    update(mainWindow->decoderWatcher->resultAt(num));
}
