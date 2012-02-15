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


#include <QtGui>
#include "QWave2/Waveform.h"
#include "QWave2/WaveformVRuler.h"
#include <QWave2/SndFile.h>
#include <QWave2/Waveform.h>
#include <QWave2/WaveformScrollBar.h>
#include <QWave2/WaveformRuler.h>
#include <QWave2/WaveformCursorProxy.h>
#include <QWave2/WaveformSelectionProxy.h>
#include <QWave2/TimeLabel.h>
#include <meaudiodecoder.h>
#include "mainwindow.h"
#include "meunity.h"
using namespace QWave2;
MEUnity* MEUnity::_unity=NULL;

MEUnity::MEUnity()
{
}

MEUnity* MEUnity::unity()
{
    if(!MEUnity::_unity)
        MEUnity::_unity=new MEUnity();
    return MEUnity::_unity;
}

QGridLayout* MEUnity::creatWaveFromPanel(QWave2::SndFile* sndFile,QWidget* parent,double time,MainWindow* mainWindow)
{
    QGridLayout* grid= new QGridLayout();
    QVBoxLayout* layout=new QVBoxLayout(parent);
    QWave2::Waveform *waveForm=new QWave2::Waveform(sndFile,0,0.0,time,parent);
    QWave2::WaveformVRuler *r = new QWave2::WaveformVRuler(parent);
//    QWave2::WaveformScrollBar* waveformScrollBar = new QWave2::WaveformScrollBar(parent);
    QMap<QString,QWave2::Waveform*> &waveForms=*(mainWindow->getWaveForm());
    waveForms[sndFile->getDecoder()->getFileName()]=waveForm;
    QWave2::WaveformRuler* ruler = new QWave2::WaveformRuler(false, parent);
    QWave2::WaveformCursorProxy* cursor=new QWave2::WaveformCursorProxy(parent);
    QWave2::WaveformSelectionProxy* selection=new QWave2::WaveformSelectionProxy(parent);

    parent->connect(selection, SIGNAL(waveformSelectionChanged(double,double,Waveform*)),
            mainWindow, SLOT(changeSelection(double,double,Waveform*)));

//    layout->addWidget(waveformScrollBar);
    grid->setSpacing(1);
    grid->addWidget((new QWidget(parent)), 0,0);
    grid->addWidget(ruler,0,1);
    int gridCurRow = 1;
    layout->addLayout(grid);
    grid->addWidget(r, gridCurRow++, 0);
    grid->addWidget(waveForm, gridCurRow++, 1);
    r->connectToWaveform(waveForm);
    r->show();

    waveForm->show();
    ruler->show();

    cursor->registerWaveform(waveForm);
    selection->registerWaveform(waveForm);

    parent->connect(waveForm, SIGNAL(waveformMouseMoved(Waveform*,double)),
            mainWindow, SLOT(setTime(Waveform*,double)));
//    waveformScrollBar->registerWaveform(waveForm);

    ruler->connectToWaveform(waveForm);


    parent->connect(mainWindow,SIGNAL(updateCursorPosition(Waveform*,double)),cursor,SLOT(updateCursorPosition(Waveform*,double)));

    return grid;
}

QVBoxLayout* MEUnity::creatTitlePanel(MEAudioDecoder* decoder)
{
    QVBoxLayout *titleLayout = new QVBoxLayout;
    QLabel *titleLable=new QLabel(decoder->getFileName());
    QString bitrate=QString("Bitrate:").append(QString::number(decoder->getBitRate()));
    QString channels=QString("Channels:").append(QString::number(decoder->getChannels()));
    QString sampleRate=QString("SampleRate:").append(QString::number(decoder->getSampleRate()));
    QLabel *bitrateLabel=new QLabel(bitrate);
    QLabel *channelsLabel=new QLabel(channels);
    QLabel *sampleRateLabel=new QLabel(sampleRate);
    titleLayout->addWidget(titleLable);
    titleLayout->addWidget(bitrateLabel);
    titleLayout->addWidget(channelsLabel);
    titleLayout->addWidget(sampleRateLabel);
    return titleLayout;
}
