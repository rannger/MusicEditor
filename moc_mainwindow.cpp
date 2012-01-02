/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Jan 2 12:48:44 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      72,   54,   11,   11, 0x08,
     119,  114,   11,   11, 0x08,
     139,  132,   11,   11, 0x08,
     174,   54,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     247,  236,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0addFiles()\0about()\0"
    "translateMusicFormat()\0newState,oldState\0"
    "stateChanged(Phonon::State,Phonon::State)\0"
    "time\0tick(qint64)\0source\0"
    "sourceChanged(Phonon::MediaSource)\0"
    "metaStateChanged(Phonon::State,Phonon::State)\0"
    "aboutToFinish()\0row,column\0"
    "tableClicked(int,int)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addFiles(); break;
        case 1: about(); break;
        case 2: translateMusicFormat(); break;
        case 3: stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 4: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: sourceChanged((*reinterpret_cast< const Phonon::MediaSource(*)>(_a[1]))); break;
        case 6: metaStateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 7: aboutToFinish(); break;
        case 8: tableClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
