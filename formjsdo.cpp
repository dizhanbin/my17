#include "formjsdo.h"
#include "my17.h"

QString JS_FormLinkCase::create_form_codes(MForm * form,const QString& arg)
{


    QString str;
    for(MLine * line : DP->formlines){

        if( line->from == form->formid ){

            MForm * toform = DP->getFormById(line->to);
            const QString & str_event = DP->getEventById( RP->getPropertyByName(toform->properties,"event")->p_value )->event_name;
            str.append("                   case R.id.btn_").append(str_event.toLower()).append(" : setFormtype(FormType.FORM_ONLY); sendMessage(Event.").append(str_event).append(");\n");
            str.append("                   break;\n");
        }
    }

    return str;

}


QString JS_LayoutLink::create_form_codes(MForm * form,const QString& arg)
{


    QString str;
    for(MLine * line : DP->formlines){

        if( line->from == form->formid ){

             MForm * toform = DP->getFormById(line->to);

            const QString & str_event = DP->getEventById( RP->getPropertyByName(toform->properties,"event")->p_value )->event_name;

            NLog::i("create_form_codes 2 %s",arg.toStdString().c_str());

            str.append( arg ).replace("${id}","android:id=\"@+id/btn_"+str_event.toLower()+"\"");
            str.replace("${text}","android:text=\""+ RP->getPropertyByName(toform->properties,"descript")->p_value  +"\"");
            str.append("\n\n");

        }
    }

    return str;

}


