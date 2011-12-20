#include <QtGui>
#include "sndfile.h"
#include "mainwindow.h"


int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Music Player");
    app.setQuitOnLastWindowClosed(true);

    MainWindow window;

    window.show();

    return app.exec();
}

