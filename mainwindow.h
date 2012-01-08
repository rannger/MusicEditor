#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>

QT_BEGIN_NAMESPACE
class QAction;
class QTableWidget;
class QLCDNumber;
QT_END_NAMESPACE

//![0]
class Plot;
class MEAudioDecoder;
class MainWindow : public QMainWindow
{
//![0]
    Q_OBJECT

public:
    MainWindow();

    QSize sizeHint() const {
        return QSize(500, 300);
    }

private slots:
    void addFiles();
    void about();
    void translateMusicFormat();
//![1]
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
//![1]

private:
    void setupActions();
    void setupMenus();
    void setupUi();

//![2]
    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QList<Phonon::MediaSource> sources;
//![2]

    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *addFilesAction;
    QAction *translateAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QLCDNumber *timeLcd;
    QTableWidget *musicTable;
    Plot *plot;
    MEAudioDecoder *decoder;
};

#endif

