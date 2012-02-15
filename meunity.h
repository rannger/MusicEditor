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

#ifndef MEUNITY_H
#define MEUNITY_H
#include <QWave2/SndFile.h>
class QGridLayout;
class QVBoxLayout;
class MEAudioDecoder;
class MainWindow;
class MEUnity
{
public:
    static MEUnity* unity();
    QGridLayout* creatWaveFromPanel(QWave2::SndFile* sndFile,QWidget* parent,double time,MainWindow* mainWindow);
    QVBoxLayout* creatTitlePanel(MEAudioDecoder* decoder);
private:
    static MEUnity* _unity;
    MEUnity();
};

#endif // MEUNITY_H
