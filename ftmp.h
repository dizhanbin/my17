#ifndef FTMP_H
#define FTMP_H

#include <QMap>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QList>
#include "nlog.h"
#include "mproperty.h"
#include <QScriptEngine>



class MForm;

class RepDo{

  public:
    virtual void rep_do(QString &strs)=0;

};


class JSDo : public QObject{

    public :
        virtual QString create_form_codes(MForm * from,const QString & arg ="" )=0;

};



class FTmp : public QObject
{
public:




    QMap<QString,QList<QString> *> tmps;

    QList<QString> lines;

    QString ftmp_path;

    explicit FTmp(QObject *parent = 0):QObject(parent){}

    //FTmp();

    void setFtmpPath(const QString & path);


    ~FTmp();

    void getTmp(const QString & key,QString &result);

    void saveTmp(const QString & path);


    void replace(const QString & tar,const QString & rep);




    void executeJS(JSDo * jsdo,MForm * form);

    static QScriptValue create_form_line_click_case(QScriptContext * qsc, QScriptEngine * qse);
    static QScriptValue create_form_line_click_case2(QScriptContext * qsc, QScriptEngine * qse);

};

#endif // FTMP_H
