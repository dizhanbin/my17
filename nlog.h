#ifndef NLOG_H
#define NLOG_H




#include <QObject>


#define MAX_LOG_LENGTH  100


class NLog : public QObject
{
    Q_OBJECT
public:
    explicit NLog(QObject *parent = 0);

public:
    static void i(const char * format,...);
    static void i(const QString &str);
    static  void outThread();
signals:

public slots:

};

#endif // NLOG_H
