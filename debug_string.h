#ifndef DEBUG_STRING_H
#define DEBUG_STRING_H
#include <QtCore>
inline void debug_string(const char *err_msg, ...)
{
    qDebug()<<err_msg;
}
#endif // DEBUG_STRING_H
