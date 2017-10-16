#ifndef FTMP_H
#define FTMP_H

#include <QMap>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QList>
#include "nlog.h"
#include "mproperty.h"


class RepDo{

  public:
    virtual void rep_do(QString &strs)=0;

};

class FTmp
{
public:


    QMap<QString,QList<QString> *> tmps;

    QList<QString> lines;

    QString ftmp_path;

    FTmp(const QString & path);

    ~FTmp();

    void getTmp(const QString & key,QString &result);

    void saveTmp(const QString & path);


    void replace(const QString & tar,const QString & rep);

};

#endif // FTMP_H
