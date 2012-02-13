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

#include "meunity.h"
#include "mainwindow.h"
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

QGridLayout* MEUnity::creatWaveFromPanel(QWave2::SndFile* sndFile,QWidget* parent,double time)
{
    QGridLayout* grid= new QGridLayout();
    QWave2::Waveform *waveForm=new QWave2::Waveform(sndFile,0,0.0,time,parent);
    QWave2::WaveformVRuler *r = new QWave2::WaveformVRuler(parent);
    QWave2::WaveformScrollBar* waveformScrollBar = new QWave2::WaveformScrollBar(parent);
    QWave2::WaveformRuler* ruler = new QWave2::WaveformRuler(false, parent);
    QWave2::WaveformCursorProxy* cursor=new QWave2::WaveformCursorProxy(parent);
    QWave2::WaveformSelectionProxy* selection=new QWave2::WaveformSelectionProxy(parent);

    parent->connect(selection, SIGNAL(waveformSelectionChanged(double,double,Waveform*)),
            parent, SLOT(changeSelection(double,double,Waveform*)));
    parent->connect(waveForm, SIGNAL(waveformMouseMoved(Waveform*,double)),
            parent, SLOT(setTime(Waveform*,double)));
    r->connectToWaveform(waveForm);
    ruler->connectToWaveform(waveForm);
    cursor->registerWaveform(waveForm);
    selection->registerWaveform(waveForm);

    grid->addWidget(ruler,2,2);
    grid->addWidget(waveformScrollBar,3,2);
    grid->addWidget(waveForm,1,2);
    grid->addWidget(r,1,1);
    waveForm->show();
    r->show();
    ruler->show();

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
