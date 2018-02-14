#include "ftmp.h"
#include <QDir>

#include "my17.h"





void FTmp::setFtmpPath(const QString & path)
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

            //NLog::i("%02d %s",i++,line.toStdString().c_str() );

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

QScriptValue FTmp::create_form_line_click_case2(QScriptContext * qsc, QScriptEngine * qse)
{

    MForm * form = (MForm*) qsc->argument(0).toQObject();
    QString text = qsc->argument(1).toString();

    JSDo * jsdo = (JSDo*)qse->globalObject().property("jsdo").toQObject();

     QString str;
     if( jsdo )
        str.append( jsdo->create_form_codes(form,text)  );


    QScriptValue sv(str);


    return sv;
}

QScriptValue FTmp::create_form_line_click_case(QScriptContext * qsc, QScriptEngine * qse)
{

    MForm * form = (MForm*) qsc->argument(0).toQObject();


    JSDo * jsdo = (JSDo*)qse->globalObject().property("jsdo").toQObject();


   // NLog::i("create_form_test %s",form->formid.toStdString().c_str());

     QString str;
     if( jsdo )
        str.append( jsdo->create_form_codes(form)  );

     /*
    for(MLine * line : DP->formlines){

        if( line->from == form->formid ){

            MForm * toform = DP->getFormById(line->to);
            const QString & str_event = DP->getEventById( RP->getPropertyByName(toform->properties,"event")->p_value )->event_name;
            str.append("            case R.id.btn_").append(str_event.toLower()).append(" : sendMessage(Event.").append(str_event).append(");\n");

        }
    }
    */



    QScriptValue sv(str);


    return sv;
}

void FTmp::executeJS(JSDo * jsdo,MForm  * formObj){




    QScriptEngine engine;

    QScriptValue qsv_form  = engine.newQObject(formObj);
    engine.globalObject().setProperty("form",qsv_form);


    QScriptValue jsdov = engine.newQObject(jsdo);
    engine.globalObject().setProperty("jsdo",jsdov);


    QScriptValue form_case = engine.newFunction(create_form_line_click_case);
    engine.globalObject().setProperty("create_form_line_click_case",form_case);


    QScriptValue form_case2 = engine.newFunction(create_form_line_click_case2);
    engine.globalObject().setProperty("create_form_line_click_case2",form_case2);


//     const QString & str_event = DP->getEventById( RP->getPropertyByName(toform->properties,"event")->p_value )->event_name;
//     QScriptValue jsdevent = engine.newQObject(str_event);
//     engine.globalObject().setProperty("event",jsdevent);



    for(int i=0;i<lines.size();i++){
        QString str = lines.at(i);
        if(str.length() > 0 )
        {
            if( str.trimmed().startsWith("<%") ){

                 QScriptValue vv =  engine.evaluate( str.replace("<%","").replace("%>","") );
                 lines.replace(i,vv.toString());

            }

        }

    }






}



