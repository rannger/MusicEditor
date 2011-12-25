#include <QtGui>
#include "mainwindow.h"
#include "OtherClass/ffmpeg.h"


int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Music Player");
    app.setQuitOnLastWindowClosed(true);
    av_register_all();
    MainWindow window;

    window.show();
    return app.exec();
}

