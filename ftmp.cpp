#include "ftmp.h"
#include <QDir>



FTmp::FTmp(const QString & path)
{

    this->ftmp_path = path;

    QFile file(this->ftmp_path);

    if( file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {


        int i=1;
        QTextStream in(&file);
        in.setCodec("UTF-8");



        while( !in.atEnd() )
        {

            QString line = in.readLine();

            lines.push_back(line);

            NLog::i("%02d %s",i++,line.toStdString().c_str() );

        }


    }




}


 void FTmp::getTmp(const QString & key,QString &result)
{

    if( tmps.contains( key) )
    {
       QList<QString> * strs = tmps.value(key);

       for(QString s : *strs)
       {

           result.append(s).append("\n");
       }



    }
    else
        result.append("not implements");


}


FTmp::~FTmp(){

    tmps.clear();
    while(!lines.isEmpty())
    lines.takeFirst();

}

void FTmp::saveTmp(const QString & path){


    QFile file(path);


    int dir_i =  path.lastIndexOf('/');
    QString dirstr = path.left(dir_i);

    QDir dir(dirstr);

    if( !dir.exists() )
        dir.mkpath( dirstr );

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return ;
    QTextStream out(&file);

    for(QString str : lines)
      out<<str<<"\r\n";
    out.flush();
    file.close();



}


void FTmp::replace(const QString & tar,const QString & rep)
{



    for(int i=0;i<lines.size();i++){
        QString str = lines.at(i);
        if(str.length() > 0 )
            lines.replace(i,str.replace(tar,rep));

    }




}



