#include "nlog.h"
#include <stdio.h>
#include <iostream>
#include <QThread>
#include <QCoreApplication>

NLog::NLog(QObject *parent) :
    QObject(parent)
{
}


void NLog::i(const char * format,...)
{


    va_list arg;
    va_start(arg,format);
    char buf[MAX_LOG_LENGTH];
    //memset(buf,'\0',sizeof(char)*MAX_LOG_LENGTH);
    vsnprintf(buf, MAX_LOG_LENGTH-3, format, arg);
    strcat(buf, "\n");
    std::cout<<buf<<std::endl;
    va_end(arg);

}

 void NLog::i(const QString &str)
{
     i(str.toStdString().c_str());

}
 void NLog::outThread()
{

    if( QThread::currentThread() ==  QCoreApplication::instance()->thread() )
    {
        NLog::i("current run in main thread.");
    }
    else
    {
        NLog::i("current run in sub thread.");
    }


}
