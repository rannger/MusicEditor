#include <QtGui>
#include "ffmpeg.h"
#include "mainwindow.h"
#include "meaudiodecoder.h"
#include "meauidoencoder.h"
#include "plot.h"
//#include "libavformat/avformat.h"
//#include "libavdevice/avdevice.h"
//#include "libswscale/swscale.h"
//#include "libavutil/fifo.h"
//#include "libavutil/avstring.h"

//![0]
MainWindow::MainWindow()
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(1000);
//![0]
//![2]
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
//![2]

//![1]
    Phonon::createPath(mediaObject, audioOutput);
//![1]
    plot=new Plot();
    decoder=new MEAudioDecoder();
    setupActions();
    setupMenus();
    setupUi();

    timeLcd->display("00:00");
}

//![6]
void MainWindow::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"),
        QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (files.isEmpty())
        return;

    int index = sources.size();
    foreach (QString string, files) {
            Phonon::MediaSource source(string);
            sources.append(source);
            decoder->dealloc();
            decoder->initWithFile(string);
            break;
    }
    if (!sources.isEmpty())
        metaInformationResolver->setCurrentSource(sources.at(index));
    QVector<double> data;
    decoder->decoder(data);
    plot->update(data);
}
//![6]

void MainWindow::about()
{
    QMessageBox::information(this, tr("About Music Player"),
        tr("The Music Player example shows how to use Phonon - the multimedia"
           " framework that comes with Qt - to create a simple music player."));
}

int ffmpeg_conver_audio(const char* input_file, const char* output_file, int samples_rate, int channel);
void MainWindow::translateMusicFormat()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"),
        QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
    QString file;
    foreach (QString string, files) {
        file=string;
        break;
    }

//    MEAudioDecoder *decoder=new MEAudioDecoder();
    decoder->dealloc();
    MEAuidoEncoder *encoder=new MEAuidoEncoder();
    int ret=0;
    qDebug()<<decoder->initWithFile(musicTable->currentItem()->text());
    qDebug()<<(ret=encoder->OpenFile(file,decoder->getSampleRate(),decoder->getChannels(),decoder));
    qDebug()<<"here";
    encoder->encoder(decoder);

    delete decoder;
    delete encoder;


}

//![9]
void MainWindow::stateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    switch (newState) {
        case Phonon::ErrorState:
            if (mediaObject->errorType() == Phonon::FatalError) {
                QMessageBox::warning(this, tr("Fatal Error"),
                mediaObject->errorString());
            } else {
                QMessageBox::warning(this, tr("Error"),
                mediaObject->errorString());
            }
            break;
//![9]
//![10]
        case Phonon::PlayingState:
                playAction->setEnabled(false);
                pauseAction->setEnabled(true);
                stopAction->setEnabled(true);
                break;
        case Phonon::StoppedState:
                stopAction->setEnabled(false);
                playAction->setEnabled(true);
                pauseAction->setEnabled(false);
                timeLcd->display("00:00");
                break;
        case Phonon::PausedState:
                pauseAction->setEnabled(false);
                stopAction->setEnabled(true);
                playAction->setEnabled(true);
;
                break;
//![10]
        case Phonon::BufferingState:
                break;
        default:

            ;
    }
    if(musicTable->columnCount())
    {
        nextAction->setEnabled(true);
        previousAction->setEnabled(true);
    }
    else
    {
        nextAction->setEnabled(false);
        previousAction->setEnabled(false);
    }
}

//![11]
void MainWindow::tick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    timeLcd->display(displayTime.toString("mm:ss"));
}
//![11]

//![12]
void MainWindow::tableClicked(int row, int /* column */)
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;

    mediaObject->stop();
    mediaObject->clearQueue();

    if (row >= sources.size())
        return;

    mediaObject->setCurrentSource(sources[row]);

    if (wasPlaying)
        mediaObject->play();
    else
        mediaObject->stop();
}
//![12]

//![13]
void MainWindow::sourceChanged(const Phonon::MediaSource &source)
{
    musicTable->selectRow(sources.indexOf(source));
    timeLcd->display("00:00");
}
//![13]

//![14]
void MainWindow::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    if (newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("Error opening files"),
            metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource())) {} /* loop */;
        return;
    }

    if (newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
            return;

    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    QString title = metaData.value(tr("TITLE"));
    QTableWidgetItem *titleItem = NULL;
    titleItem=new QTableWidgetItem(metaInformationResolver->currentSource().fileName());

    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);

//    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
//    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
//    QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
//    albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
//    QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));
//    yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);

    int currentRow = musicTable->rowCount();
    musicTable->insertRow(currentRow);
    musicTable->setItem(currentRow, 0, titleItem);
//    musicTable->setItem(currentRow, 1, artistItem);
//    musicTable->setItem(currentRow, 2, albumItem);
//    musicTable->setItem(currentRow, 3, yearItem);


    if (musicTable->selectedItems().isEmpty()) {
        musicTable->selectRow(0);
        mediaObject->setCurrentSource(metaInformationResolver->currentSource());
    }

    Phonon::MediaSource source = metaInformationResolver->currentSource();
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }
    else {
        musicTable->resizeColumnsToContents();
        if (musicTable->columnWidth(0) > 300)
            musicTable->setColumnWidth(0, 1000);
    }
}
//![15]

//![16]
void MainWindow::aboutToFinish()
{
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
    }
}
//![16]

void MainWindow::setupActions()
{
    playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(tr("Ctrl+P"));
    playAction->setDisabled(true);
    pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAction->setShortcut(tr("Ctrl+A"));
    pauseAction->setDisabled(true);
    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(true);
    nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction->setShortcut(tr("Ctrl+N"));
    nextAction->setDisabled(true);
    previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction->setShortcut(tr("Ctrl+R"));
    previousAction->setDisabled(true);
    addFilesAction = new QAction(tr("Add &Files"), this);
    addFilesAction->setShortcut(tr("Ctrl+F"));
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setShortcut(tr("Ctrl+Q"));
    translateAction = new QAction(style()->standardIcon(QStyle::SP_DirClosedIcon),tr("Wav to mp3"),this);

//![5]
    connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()) );
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
//![5]
    connect(addFilesAction, SIGNAL(triggered()), this, SLOT(addFiles()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(translateAction, SIGNAL(triggered()), this, SLOT(translateMusicFormat()));
}

void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addFilesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
//    QMenu* translateMenu=menuBar()->addMenu(tr("&Translate"));
//    translateMenu->addAction(translateAction);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);
}

//![3]
void MainWindow::setupUi()
{
//![3]
    QToolBar *bar = new QToolBar;
    bar->addAction(previousAction);
    bar->addAction(playAction);
    bar->addAction(pauseAction);
    bar->addAction(stopAction);   
    bar->addAction(nextAction);
    bar->addAction(translateAction);

//![4]
    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setMediaObject(mediaObject);

    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
//![4]
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QLabel *volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    QStringList headers;
//    headers << tr("Title") << tr("Artist") << tr("Album") << tr("Year");
    headers<<tr("file name");
    musicTable = new QTableWidget(0, 1);
    musicTable->setHorizontalHeaderLabels(headers);
    musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(musicTable, SIGNAL(cellPressed(int,int)),
            this, SLOT(tableClicked(int,int)));

    QHBoxLayout *seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(seekSlider);
    seekerLayout->addWidget(timeLcd);

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(bar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(volumeLabel);
    playbackLayout->addWidget(volumeSlider);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    plot->resize(600,400);
    mainLayout->addWidget(plot);

    mainLayout->addWidget(musicTable);
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    setWindowTitle("Music Editor");
}

