#include "my17.h"
#include <qxmlstream.h>
#include "viewgroup.h"
#include "iconview.h"
#include "lineview.h"
#include "mproperty.h"
#include "ftmp.h"

using namespace my17;

static R* s_r_instance = NULL;
static D* s_d_instance = NULL;

R* R::getInstance()
{

    if( s_r_instance == NULL )
        s_r_instance = new R();
    return s_r_instance;

}

void R::loadElements()
{


    QFile file( DATA_DIR ( "elements.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();


        MElement * ele;
        while( !reader.atEnd() )
        {

            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "element" )
                {
                    ele = new MElement();
                    ele->ele_id = reader.attributes().value("id").toString();
                    ele->name = reader.attributes().value("name").toString();
                    ele->iconpath = reader.attributes().value("iconpath").toString();
                    ele->descript = reader.attributes().value("descript").toString();
                    if( reader.attributes().hasAttribute("c_android") )
                        ele->c_android = reader.attributes().value("c_android").toString();
                    if( reader.attributes().hasAttribute("c_ios") )
                        ele->c_ios = reader.attributes().value("c_ios").toString();


                }
                else if( name == "property" )
                {

                    MProperty * mp = new MProperty();
                    ele->properties.push_back(mp);

                    mp->p_name = reader.attributes().value("name").toString();
                    mp->p_title = reader.attributes().value("title").toString();
                    mp->p_type = reader.attributes().value("type").toString().toInt();
                    mp->p_args = reader.attributes().value("args").toString();
                    mp->p_value =  reader.attributes().value("value").toString();

                }
            }
            else if( reader.isEndElement() )
            {
                if( name == "element" )
                {
                    elements.push_back(ele);
                }
            }

            reader.readNext();

        }


    }


}



D* D::getInstance()
{

    if( s_d_instance == NULL )
        s_d_instance = new D();
    return s_d_instance;

}

void D::loadModel()
{

    QFile file(DATA_DIR ("models.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MModelDelegate * mmd = NULL;
        MModelFieldDelegate * field = NULL;
        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "model" )
                {
                    mmd =  newModel();

                    mmd->name = reader.attributes().value("name").toString();
                    if( reader.attributes().hasAttribute("id") )
                        mmd->id = reader.attributes().value("id").toString();
                    else
                        mmd->id = RP->getId();

                }
                else if( name== "field" )
                {
                    field = new MModelFieldDelegate();
                    mmd->fields.push_back(field);
                }
                else if( name == "name")
                {
                    field->field_name = reader.readElementText();

                }else if( name == "type")
                {

                    field->field_type = reader.readElementText().toInt();

                }
                else if( name == "value" )
                {
                    field->field_value = reader.readElementText();

                }
                else if( name == "descript" )
                {

                    field->field_descript = reader.readElementText();

                }


            }
            else if( reader.isEndElement() )
            {



            }



            reader.readNext();
        }



    }


}

bool D::saveModel()
{

    QFile file(DATA_DIR ("models.xml"));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("models");

        for(int i=0;i<models.size();i++)
        {


            MModelDelegate *model = models.at(i);
            writer.writeStartElement("model");
            writer.writeAttribute("name",model->name);
            writer.writeAttribute("id",model->id);
            for(int k=0;k<model->fields.size();k++)
            {
                MModelFieldDelegate * field = model->fields.at(k);
                writer.writeStartElement("field");
                writer.writeTextElement("name",field->field_name);
                writer.writeTextElement("type",QString::number(field->field_type));
                writer.writeTextElement("value",field->field_value);
                writer.writeTextElement("descript",field->field_descript);
                writer.writeEndElement();
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;
}



bool D::saveEvents()
{

    QFile file(DATA_DIR ("events.xml"));


    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("events");

        for(int i=0;i<events.size();i++)
        {
            MEventDelegate *event = events.at(i);
            writer.writeStartElement("event");
            if( event->event_id.length() == 0 )
                event->event_id = RP->getId();
            writer.writeTextElement("id",event->event_id);
            writer.writeTextElement("name",event->event_name);
            writer.writeTextElement("type",QString::number(event->event_type) );
            writer.writeTextElement("descript",event->event_descript);
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;

}

bool event_comparator( MEventDelegate *s1, const MEventDelegate *s2)
{
    return s1->operator <( s2 );
}


void D::loadEvents()
{
    QFile file(DATA_DIR ("events.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MEventDelegate * med = NULL;

        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "event" )
                {
                    med = new MEventDelegate();
                    events.push_back(med);

                }

                else if( name == "id")
                {
                    med->event_id = reader.readElementText();

                }
                else if( name == "name")
                {
                    med->event_name = reader.readElementText();

                }else if( name == "type")
                {

                    med->event_type = reader.readElementText().toInt();

                }

                else if( name == "descript" )
                {

                    med->event_descript = reader.readElementText();

                }


            }
            else if( reader.isEndElement() )
            {



            }



            reader.readNext();
        }

        file.close();


        qSort(events.begin(),events.end(),event_comparator);
        //qSort(events.begin(),events.end(),event_comparator);



    }


    if( events.size() == 0 ){

       MEventDelegate * med0 = new MEventDelegate();
       med0->event_name = "SYS_DIALOG_INFO";
       med0->event_type = T_SYS;
       med0->event_descript = "消息提示框";

       MEventDelegate * med1 = new MEventDelegate();
       med1->event_name = "SYS_DIALOG_SURE";
       med1->event_type = T_SYS;
       med1->event_descript = "弹出确认对话框";

       MEventDelegate * med2 = new MEventDelegate();
       med2->event_name = "SYS_FORM_BACK";
       med2->event_type = T_SYS;
       med2->event_descript = "页面返回";


       MEventDelegate * med3 = new MEventDelegate();
       med3->event_name = "SYS_FROM_CLEAR";
       med3->event_type = T_SYS;
       med3->event_descript = "清空堆栈中所有页面";


       MEventDelegate * med4 = new MEventDelegate();
       med4->event_name = "SYS_NONE";
       med4->event_type = T_SYS;
       med4->event_descript = "空事件";


       MEventDelegate * med5 = new MEventDelegate();
       med5->event_name = "SYS_PUSH_TO_AND_CLEAR_ALL";
       med5->event_type = T_SYS;
       med5->event_descript = "进入并清除所有界面";

       MEventDelegate * med6 = new MEventDelegate();
       med6->event_name = "SYS_TOAST";
       med6->event_type = T_SYS;
       med6->event_descript = "提示信息";

       MEventDelegate * med7 = new MEventDelegate();
       med7->event_name = "SYS_WAITTING_HIDE";
       med7->event_type = T_SYS;
       med7->event_descript = "隐藏等待框";

       MEventDelegate * med8 = new MEventDelegate();
       med8->event_name = "SYS_WAITTING_SHOW";
       med8->event_type = T_SYS;
       med8->event_descript = "等待框";


       events.push_back(med0);
       events.push_back(med1);
       events.push_back(med2);
       events.push_back(med3);
       events.push_back(med4);
       events.push_back(med5);
       events.push_back(med6);
       events.push_back(med7);
       events.push_back(med8);


    }


}





bool D::saveBusiness()
{

    QFile file(DATA_DIR ("business.xml"));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("business");

        for(int i=0;i<business.count();i++)
        {

            writer.writeStartElement("item");
            MBusinessDelegate *model = business.at(i);
            writer.writeAttribute("name",model->name);
            writer.writeAttribute("type",QString::number(model->type) );
            writer.writeAttribute("alia",model->alia);
            model->viewgroup->save(writer);
            writer.writeEndElement();


        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;


}

bool business_comparator( MBusinessDelegate *s1, const MBusinessDelegate *s2)
{
    return s1->name.compare(s2->name)>0;
}


void D::loadBusiness()
{


    QFile file(DATA_DIR ("business.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MBusinessDelegate * med = NULL;
        View * view = NULL;

        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            NLog::i("name %s",name.toString().toStdString().c_str() );
            if( reader.isStartElement() )
            {
                if( name == "item" )
                {


                    med = newBusiness();
                    med->name = reader.attributes().value("name").toString();

                    if( reader.attributes().hasAttribute("alia") )
                        med->alia = reader.attributes().value("alia").toString();

                    if( reader.attributes().hasAttribute("type") )
                        med->type = reader.attributes().value("type").toInt();
                    else
                        med->type = 1;

                }
                else if( name == "view" )
                {
                    QString type = reader.attributes().value("type").toString();

                    NLog::i("view type:%s",type.toStdString().c_str());

                    View * view = createView(type );

                    if( !  view->load(reader) )
                    {
                        NLog::i("read type:%s error",type.toStdString().c_str());
                        return ;
                    }
                    med->viewgroup->addView(view);

                }
                else if( name == "Line" )
                {
                    View * view = createView("LineView");

                    med->viewgroup->addView(view);
                    if( !  view->load(reader) )
                    {
                        NLog::i("read LineView error");
                        return ;
                    }

                }

            }else if( reader.isEndElement() )
            {

                if( name == "item" )
                    dealLine(med);
            }



            reader.readNext();
        }





        file.close();

    }

    qSort(business.begin(),business.end(),business_comparator);



}


bool D::saveForms()
{

    QFile file(DATA_DIR( "forms.xml" ));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("forms");

        for(int i=0;i<forms.count();i++)
        {

            writer.writeStartElement("form");
            MForm *model = forms.at(i);
            writer.writeAttribute("id",model->formid );

            writer.writeTextElement("x",QString::number( model->x ) );
            writer.writeTextElement("y",QString::number( model->y ) );
            writer.writeTextElement("w",QString::number( model->w ) );
            writer.writeTextElement("h",QString::number( model->h ) );


            saveProperties(model->properties,writer,"data");
            writer.writeEndElement();


        }

        for(int i=0;i<formlines.count();i++)
        {
            MLine * line = formlines.at(i);
            writer.writeStartElement("Line");

            writer.writeAttribute("id",line->lineid );

            writer.writeTextElement("from",line->from) ;
            writer.writeTextElement("to",line->to );

            saveProperties(line->properties,writer,"condition");

            writer.writeEndElement();
        }


        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;

}


bool D::loadProperties(QList<MProperty *> & properties, QXmlStreamReader &reader )
{

    MProperty * mp = NULL;
    while( true )
    {
        reader.readNext();

        QString name = reader.name().toString();

        if( reader.isStartElement() )
        {
            if( name == "property" )
            {
                mp = new MProperty();
                properties.push_back(mp);

                mp->p_name = reader.attributes().value("name").toString();
                mp->p_title = reader.attributes().value("title").toString();
                mp->p_type = reader.attributes().value("type").toInt();
                mp->p_args = reader.attributes().value("args").toString();
                mp->p_value = reader.attributes().value("value").toString();



            }
        }
        else if( reader.isEndElement() )
        {

            if( name == "data" || name == "condition" )

                return true;

        }


    }
    return true;


}

bool D::saveProperties(QList<MProperty *> & properties,QXmlStreamWriter &writer,const QString &tag)
{
    writer.writeStartElement(tag);

    for( int i=0;i<properties.count();i++)
    {
        MProperty * p = properties.at(i);
        writer.writeStartElement("property");
        writer.writeAttribute("name",p->p_name);
        writer.writeAttribute("title",p->p_title);
        writer.writeAttribute("type",QString::number(p->p_type));
        writer.writeAttribute("args",p->p_args);
        writer.writeAttribute("value",p->p_value);
        writer.writeEndElement();
    }

    writer.writeEndElement();
    return false;
}

void D::loadForms()
{

    QFile file(DATA_DIR ("forms.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MForm * form = NULL;
        MLine * line = NULL;

        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "form" )
                {
                    form = new MForm();
                    forms.push_back(form);
                    form->formid = reader.attributes().at(0).value().toString();

                }
                else if( name == "Line" )
                {
                    line = new MLine();
                    formlines.push_back(line);
                    line->lineid = reader.attributes().at(0).value().toString();
                }
                else if( name == "from" )
                {

                    line->from = reader.readElementText();
                }
                else if( name == "to" )
                {

                    line->to = reader.readElementText();
                }
                else if( name == "condition" )
                {
                    loadProperties(line->properties,reader);
                }
                else if( name == "data" )
                {
                    loadProperties(form->properties,reader);
                }
                else if( name == "x" )
                    form->x = reader.readElementText().toInt();
                else if( name == "y" )
                    form->y = reader.readElementText().toInt();
                else if( name == "w" )
                    form->w = reader.readElementText().toInt();
                else if( name == "h" )
                    form->h = reader.readElementText().toInt();



            }
            else if( reader.isEndElement() )
            {



            }



            reader.readNext();
        }

        file.close();

    }
}




View * D::getView(MBusinessDelegate * mbd,const QString viewid)
{
    View * view = NULL;
    for(int i=0;i<mbd->viewgroup->m_children.count();i++)
    {
        view = mbd->viewgroup->m_children.at(i);
        if( view->viewid == viewid )
        {

            return view;

        }
    }
    return NULL;

}

void D::dealLine(MBusinessDelegate * mbd)
{

    if( mbd )
    {

        View * view = NULL;
        for(int i=0;i<mbd->viewgroup->m_children.count();i++)
        {
            view = mbd->viewgroup->m_children.at(i);
            if( view->isLine() )
            {
                LineView * line = (LineView *)view;
                view->line( getView(mbd,line->fromid),getView(mbd,line->toid ) );

            }
        }


    }


}

View * D::createView(const QString & name)
{

    if( name == "IconView" )
    {
        return new IconView();
    }else if( name == "LineView" )
    {

        return new LineView();

    }


    return NULL;

}

bool D::saveProjectInfos()
{
    QFile file(DATA_DIR("projectinfos.xml"));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("project");

        for(int i=0;i<projectinfos.size();i++)
        {
            MData *md = projectinfos.at(i);
            writer.writeStartElement("data");

            writer.writeAttribute("key",md->key);
            writer.writeAttribute("value",md->value);
            writer.writeAttribute("descript",md->descript );
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;
}
void D::loadProjectInfos()
{

    QFile file(DATA_DIR("projectinfos.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();



        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "data" )
                {
                    MData  * data = new MData();

                    data->key = reader.attributes().value("key").toString();
                    data->value = reader.attributes().value("value").toString();
                    data->descript = reader.attributes().value("descript").toString();

                    projectinfos.push_back(data);

                }

            }



            reader.readNext();
        }

        file.close();

    }
    else{
        MData  * data_lib = new MData();
        data_lib->key = "#package";
        data_lib->value = "com.lrl.lrlib.data";
        data_lib->descript = "lrlib package";


        MData  * data_project = new MData();
        data_project->key = "#project";
        data_project->value = "com.*";
        data_project->descript = "project package";


        projectinfos.push_back(data_lib);
        projectinfos.push_back(data_project);

    }



}

bool D::saveUrl()
{

    QFile file(DATA_DIR("urls.xml"));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("urls");

        for(int i=0;i<urls.size();i++)
        {
            MUrlDelegate *url = urls.at(i);
            writer.writeStartElement("url");

            writer.writeTextElement("id",url->url_id);
            writer.writeTextElement("name",url->url_name);
            writer.writeTextElement("address", url->url_address );
            writer.writeTextElement("descript",url->url_descript );
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


        return true;
    }
    return false;


}
void D::loadUrl()
{



    QFile file(DATA_DIR ("urls.xml"));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MUrlDelegate * med = NULL;

        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
                if( name == "url" )
                {
                    med = new MUrlDelegate();
                    urls.push_back(med);


                }
                else if( name == "id")
                {
                    med->url_id = reader.readElementText();
                }

                else if( name == "name")
                {
                    med->url_name = reader.readElementText();

                }else if( name == "address")
                {

                    med->url_address =  reader.readElementText();

                }

                else if( name == "descript" )
                {

                    med->url_descript = reader.readElementText();

                }


            }



            reader.readNext();
        }

        file.close();

    }




}


int  D::getModelIndexById(const QString &id)
{
    if( id.length() == 0 )
        return -1;
    for(int i=0;i<models.count();i++)
    {

        if( models.at(i)->id == id )
            return i;

    }
    return -1;


}

int D::getEventIndexById(const QString &id)
{

    if( id.length() == 0 )
        return -1;
    for(int i=0;i<events.count();i++)
    {

        if( events.at(i)->event_id == id )
            return i;

    }
    return -1;

}

int D::getUrlIndexById(const QString &id)
{
    if( id.length() == 0 )
        return -1;
    for(int i=0;i<urls.count();i++)
    {

        if( urls.at(i)->url_id == id )
            return i;

    }
    return -1;


}


MModelDelegate * D::getModelById(const QString &id)
{
    if( id.length() == 0 ) return NULL;
    for(MModelDelegate * mm : models)
        if( mm->id == id )
            return mm;
    return NULL;

}
MEventDelegate * D::getEventById(const QString &id)
{
    if( id.length() == 0 ) return NULL;
    for(MEventDelegate * mm : events)
        if( mm->event_id == id )
            return mm;
    return NULL;

}

MUrlDelegate * D::getUrlById(const QString &id)
{
    if( id.length() == 0 ) return NULL;
    for( MUrlDelegate * mm : urls)
    {
        if( mm->url_id == id )
            return mm;

    }
    return NULL;

}


bool D::createEvent()
{


    if( true )
    {
        QString strs = "/* create my 17 */\n";


        MData * data = DP->getProjectInfo("#package");

        strs.append("package ").append(data->value).append(";\n");

        strs.append("public enum Event{\n\n");

        for(int i=0;i<events.count();i++)
        {

            MEventDelegate * event = events.at(i);

            strs.append("  ").append(event->event_name);
            if( events.count()-1 == i)
                strs.append(";//");
            else
                strs.append(",//");
            strs.append(event->event_descript).append("\n");


        }


        strs.append("\n}\n");


        QFile file(DATA_OUT_DIR("java/Event.java"));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;

    }
    if( true )
    {


        QString strs = "/* create my 17 */\n";


        strs.append("#import <Foundation/Foundation.h>\n");



        strs.append("typedef enum{\n\n");

        for(int i=0;i<events.count();i++)
        {

            MEventDelegate * event = events.at(i);

            strs.append("  ").append(event->event_name);
            if( events.count()-1 == i)
                strs.append("//");
            else
                strs.append(",//");
            strs.append(event->event_descript).append("\n");


        }


        strs.append("} Event;\n\n");



        strs.append("@interface EventUtil : NSObject\n\n");

        strs.append("+(Event) event_by_str:(NSString *)eventstr;\n\n");
        strs.append("+(NSString*)str_by_event:(Event)event;\n\n");

        strs.append("@end\n");









        QFile file(DATA_OUT_DIR("ios/event.h"));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;


    }
    if( true )
    {


        QString strs = "/* create my 17 */\n";


        strs.append("#import \"event.h\"\n");



        strs.append("@implementation EventUtil\n\n");


        strs.append("+(Event) event_by_str:(NSString *)eventstr{\n");
        for(int i=0;i<events.count();i++)
        {

            MEventDelegate * event = events.at(i);

            strs.append("  if( [eventstr isEqual:@\"").append(event->event_name).append("\"] ) return ").append(event->event_name).append(";\n");




        }

        strs.append("  return -1;\n");
        strs.append("}\n\n");


        strs.append("+(NSString*)str_by_event:(Event)event{\n");

        strs.append("  switch(event){\n\n");

        for(int i=0;i<events.count();i++)
        {

            MEventDelegate * event = events.at(i);

            strs.append("  case ").append(event->event_name).append(" : return @\"").append(event->event_name).append("\";\n");


        }

        strs.append("}\n\n");
        strs.append("  return @\"not define\";\n");
        strs.append("}\n\n");






        strs.append("@end\n");




        QFile file(DATA_OUT_DIR("ios/event.m"));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;


    }
    return true;
}
bool D::createUrls()
{

    QString strs = "/* create my 17 */\n";
    strs.append("public class Urls{\n\n");

    for(int i=0;i<urls.count();i++)
    {

        MUrlDelegate * url = urls.at(i);

        strs.append("  public static final String ")
                .append(url->url_name)
                .append(" = \"")
                .append( url->url_address )
                .append("\";//")
                .append(url->url_descript)
                .append("\n");

    }


    strs.append("\n}\n");


    QFile file(DATA_OUT_DIR("java/Urls.java"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out<<strs;


    return true;
}


bool d_create_form_code(MForm * form)
{

   MProperty * formp = RP->getPropertyByName(form->properties,"android");
   if( !formp )
       return false;

   MProperty * form_java = RP->getPropertyByName(form->properties,"java_plate");
   if( !form_java )
       return false;

   MProperty * form_layout = RP->getPropertyByName(form->properties,"layout_plate");
   if( !form_layout )
       return false;


   QString java_path = DATA_PLATE_DIR(form_java->p_value).append(".java");
   QString layout_path = DATA_PLATE_DIR(form_layout->p_value).append(".xml");



   QFile java_file(java_path);
   if( java_file.exists() ){

       FTmp java_ftmp(java_path);
       java_ftmp.replace("${descript}",formp->p_title);
       java_ftmp.replace("${android}",formp->p_value);
       java_ftmp.replace( "${layout_plate}",formp->p_value.toLower().replace("form","form_") );
       QString java_out = DATA_OUT_DIR("java/forms/").append(formp->p_value).append(".java");

       java_ftmp.saveTmp(java_out);

   }

   QFile layout_file(layout_path);
   if( layout_file.exists() ){

       FTmp java_ftmp(layout_path);
       //java_ftmp.replace("${android}",formp->p_value);
       //java_ftmp.replace( "${layout_plate}",formp->p_value.toLower().replace("form","form_") );
       QString java_out = DATA_OUT_DIR("java/forms/").append(formp->p_value.toLower().replace("form","form_")).append(".xml");
       java_ftmp.saveTmp(java_out);

   }


    if( true ){


        return true;
    }

    if( true )//andoird
    {

        MData * data = DP->getProjectInfo("#package");


        QString strs = "/* create my 17 */\n";

        strs.append("package ").append(data->value).append(".forms;\n");

        strs.append("import ").append("com.lrl.lrlib.Form;\n\n");


        MProperty * formp = RP->getPropertyByName(form->properties,"android");


        if( !formp )
            return false;

        strs.append("public class ").append(formp->p_value).append("  extends Form{\n\n");




        strs.append("\n}\n");

        QString filename = DATA_OUT_DIR("");
        filename.append("java/").append( formp->p_value).append(".java");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;

    }
    if( true )
    {


        QString strs = "/* create my 17 */\n";


        MProperty * formp = RP->getPropertyByName(form->properties,"android");


        if( !formp )
            return false;



        strs.append("#import <UIKit/UIKit.h>\n");
        strs.append("#import \"Form.h\"\n");
        strs.append("@interface  ").append(formp->p_value).append("  : Form\n\n\n\n");


        // strs.append("-(BOOL)onMessage:(Event) event value:(id) value;\n\n");


        strs.append("@end\n");

        QString filename = DATA_OUT_DIR("");
        filename.append("ios/").append( formp->p_value).append(".h");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;



    }

    if( true )
    {


        QString strs = "/* create my 17 */\n";


        MProperty * formp = RP->getPropertyByName(form->properties,"android");


        if( !formp )
            return false;



        strs.append("#import \"").append(formp->p_value).append(".h\"\n");

        strs.append("@implementation ").append(formp->p_value).append("  \n\n\n\n");


        strs.append("-(BOOL)onMessage:(Event) event value:(id) value{\n\n");

        strs.append("  return FALSE;\n\n");

        strs.append("}\n\n");


        strs.append("@end\n");

        QString filename = DATA_OUT_DIR("");
        filename.append("ios/").append( formp->p_value).append(".m");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;



    }


    return true;
}

bool D::createForms()
{




    {//andoird
        QString strs = "/* create my 17 */\n";


        MData * data = DP->getProjectInfo("#package");

        strs.append("package ").append(data->value).append(";\n");

        strs.append("import ").append(data->value).append(".forms.*;\n");
        strs.append("import com.lrl.lrlib.LFormFactory;\n");




        strs.append("public class FormFactory implements LFormFactory<Event>{\n");
        strs.append("  public  Class getForm(Event event){\n");
        strs.append("      switch(event){\n");


        for(int i=0;i<forms.count();i++)
        {

            MForm * form = forms.at(i);


            const QString & str_event = RP->getPropertyByName(form->properties,"event")->p_value;
            const QString & str_android = RP->getPropertyByName(form->properties,"android")->p_value;

            MEventDelegate * me =  DP->getEventById( str_event );

            if( me && me->event_name.length() > 0 )
                strs.append("          case ").append(me->event_name).append(": return ")
                        .append(  str_android  ).append(".class;\n");

            d_create_form_code(form);

        }

        strs.append("      }\n");
        strs.append("      return null;\n");
        strs.append("  }\n");




        strs.append("  public  String getFormName(Event event){\n");
        strs.append("      switch(event){\n");

        for(int i=0;i<forms.count();i++)
        {

            MForm * form = forms.at(i);


            const QString & str_event = RP->getPropertyByName(form->properties,"event")->p_value;
            const QString & str_name = RP->getPropertyByName(form->properties,"descript")->p_value;



            MEventDelegate * me =  DP->getEventById( str_event );

            if( me && me->event_name.length() > 0 )
                strs.append("          case ").append(me->event_name).append(": return \"")
                        .append(  str_name  ).append("\";\n");



        }
        strs.append("      }\n");
        strs.append("      return \"\";\n");
        strs.append("  }\n");

        strs.append("}\n");



        QString filename = DATA_OUT_DIR("");
        filename.append("java/FormFactory.java");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;
        file.close();









    }
    {

        QString strs = "/* create my 17 */\n";

        strs.append("#import <Foundation/Foundation.h>\n\n");
        strs.append("#import \"event.h\"\n\n");


        strs.append("@interface FormFactory : NSObject\n");
        strs.append("+(NSString*) getForm:(Event) event;\n");


        strs.append("@end;\n");

        QString filename = DATA_OUT_DIR("");
        filename.append("ios/FormFactory.h");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;




    }


    {//.m

        QString strs = "/* create my 17 */\n";

        strs.append("#import \"FormFactory.h\"\n\n");

        strs.append("@implementation FormFactory\n\n");
        strs.append("+(NSString*) getForm:(Event) event{\n");

        strs.append("      switch(event){\n");

        for(int i=0;i<forms.count();i++)
        {

            MForm * form = forms.at(i);


            const QString & str_event = RP->getPropertyByName(form->properties,"event")->p_value;
            const QString & str_android = RP->getPropertyByName(form->properties,"android")->p_value;

            MEventDelegate * me =  DP->getEventById( str_event );


            if( me && me->event_name.length() > 0 )
                strs.append("          case ").append(me->event_name).append(": return @\"")
                        .append(  str_android  ).append("\";\n");

            d_create_form_code(form);

        }

        strs.append("     }\n");
        strs.append("     return nil;\n");


        strs.append("}\n\n@end\n");
        QString filename = DATA_OUT_DIR("");
        filename.append("ios/FormFactory.m");

        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out(&file);
        out<<strs;




    }






    return true;
}


void createBusiness_one(MBusinessDelegate * mbd)
{
    QString path = DATA_OUT_DIR("");
    path.append(mbd->alia).append(".xml");

    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("business");

        writer.writeAttribute("descript",mbd->name);

        mbd->viewgroup->createCodes(writer);
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();


    }




}

bool  createModel( MModelDelegate * md)
{


    if(true)  {


        //android
        QString path = DATA_OUT_DIR("java/");
        path.append(md->name).append(".java");


        QString strs = "/* create my 17 */\n";

        MData * data = DP->getProjectInfo("#package");

        strs.append("package ").append(data->value).append(".model;\n");


        strs.append("import java.util.List;\n\n");
        strs.append("public class ").append(md->name).append("{\n\n");


        for(int i=0;i<md->fields.count();i++)
        {
            MModelFieldDelegate * field = md->fields.at(i);



            QString fieldstr;

            if( field->field_type == 4 )
                fieldstr.append(field->field_value);
            else if( field->field_type ==  3 )
                fieldstr.append("List<").append(field->field_value).append("> ");
            else
                fieldstr.append( RP->model_field_type_index(field->field_type) );





            strs.append("  public ").
                    append( fieldstr ).
                    append(" ").
                    append(field->field_name).
                    append(";//").append(field->field_descript).append("\n");


        }


        strs.append("\n}\n");

        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {


            QTextStream out(&file);
            out<<strs;


        }
        else
            return false;
    }



    QString strs_arrays;




    if(true) {

        //ios
        QString path = DATA_OUT_DIR("ios/");
        path.append(md->name).append(".h");



        QString strs_include = "/* create my 17 */\n";
        strs_include.append("#import <Foundation/Foundation.h>\n\n ");

        QString strs = "";


        strs.append("@interface ").append(md->name).append(" : NSObject\n\n");


        for(int i=0;i<md->fields.count();i++)
        {
            MModelFieldDelegate * field = md->fields.at(i);



            strs.append("@property  ").
                    append( field->field_type  != 4 ? RP->model_field_type_index_ios(field->field_type) : "(retain,nonatomic) "+field->field_value +" * ").
                    append(" ").
                    append(field->field_name).
                    append(";//").append(field->field_descript).append("\n");

            if( field->field_type ==  4 )
            {

                strs_include.append("#import \"").append(field->field_value).append(".h\"\n");

            }
            else if( field->field_type ==  3 )
            {


                strs_arrays.append("                    @\"").append(field->field_name).append("\" : @\"").append(field->field_value ).append("\",\n");

            }



        }


        strs.append("\n@end\n");

        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {


            QTextStream out(&file);
            out<<strs_include<<strs;


        }
        else
            return false;








    }


    if( true )//.m
    {

        QString path = DATA_OUT_DIR("ios/");
        path.append(md->name).append(".m");



        QString strs = "/* create my 17 */\n";
        strs.append("#import \"").append(md->name).append(".h\"\n\n ");

        strs.append("@implementation  ").append(md->name).append(" \n\n");


        strs.append("+ (NSDictionary *)objectClassInArray\n");
        strs.append("{\n");


        strs.append("    return @{\n");

        strs.append( strs_arrays );
        //strs.append("                    @\"objInfo\" : @\"OAItoProjectInfoModel\",\n");
        strs.append("             };\n");

        strs.append("}\n");



        strs.append("\n@end\n");

        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {


            QTextStream out(&file);
            out<<strs;
            return true;

        }




    }

    return false;











    return false;
}

bool D::createModels()
{

    for(int i=0;i<models.count();i++)
    {

        MModelDelegate * md = models.at(i);

        createModel(md);


    }
    return true;

}

bool D::createProjectInfos()
{

    const QString from_dir = DATA_DIR( "projectinfos.xml");
    const QString to_dir = DATA_OUT_DIR("projectinfos.xml");
    return QFile::copy(from_dir,to_dir);

}


bool D::createStrings()
{


    if(true)  {


        //android
        QString path = DATA_OUT_DIR("java/");
        path.append("Strings.java");


        QString strs = "/*create my 17 */\n";


        MData * data = DP->getProjectInfo("#package");
        MData * data_p = DP->getProjectInfo("#project");

        strs.append("package ").append(data->value).append(";\n");

        strs.append("import ").append(data_p->value).append(".R;\n");

        strs.append("public class ").append("Strings").append("{\n\n");

        strs.append("  public static int getStringByKey(String k){\n\n");

        strs.append("        switch(k){\n");

        QMap<QString,MData*>::iterator it;
        for(it = qlobal_strings.begin();it != qlobal_strings.end();++it)
        {

            MData * data = it.value();


            strs.append("           case ").append("\"").append(data->key).append("\": return R.string.").append(data->key.right(data->key.length()-2)).append(" ;//");
            strs.append(data->descript).append("\n");
        }


        /*
       for(int i=0;i< global_strings.size();i++ )
       {
           MData * data = global_strings.at(i);
       strs.append("           case ").append("\"").append(data->key).append("\": return R.string. ;//");
       strs.append(data->descript).append("\n");
       }
        */

        strs.append("        }\n");
        strs.append("        return 0;\n\n");
        strs.append("  }\n\n");
        strs.append("}\n");

        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {


            QTextStream out(&file);
            out<<strs;


        }
        else
            return false;
    }


}

bool D::createBusiness()
{



    if( true )
    {

        QString event_xmls;

        MData * data = DP->getProjectInfo("#package");

        event_xmls.append("package ").append(data->value).append(";\n");

        event_xmls.append("public class FlowBoxs{\n");
        event_xmls.append("    public static String getBox(Event event){\n");
        event_xmls.append("        switch(event){\n");







        for(int i=0;i<business.count();i++)
        {

            MBusinessDelegate * mbd = business.at(i);

            View * view = mbd->viewgroup->getStart();

            if( view )
            {
                MProperty * mp = view-> getProperty("event");
                if( mp )
                {
                    MEventDelegate * me =   DP->getEventById(mp->p_value);
                    if( me )
                    {
                        event_xmls.append("         case ").append( me->event_name ).append(": return \"flows/").append(mbd->alia).append(".xml\";\n");
                        //NLog::i("event %s  -->%s.xml",me->event_name.toStdString().c_str(),mbd->alia.toStdString().c_str() );
                    }
                }

            }

            createBusiness_one(mbd);


        }

        event_xmls.append("        }\n");
        event_xmls.append("        return null;\n");
        event_xmls.append("    }\n");
        event_xmls.append("}\n");



        createFile(DATA_OUT_DIR("java/FlowBoxs.java"),event_xmls);

    }

    if( true )//ios
    {


        QString event_xmls;

        event_xmls.append("#import <Foundation/Foundation.h>\n");
        event_xmls.append("#import \"FlowBox.h\"\n");
        event_xmls.append("#import \"event.h\"\n");


        event_xmls.append("@interface FlowBoxs : NSObject\n");

        event_xmls.append("+(NSString*) getBox:(Event)event;\n");

        event_xmls.append("@end \n");


        createFile(DATA_OUT_DIR("ios/FlowBoxs.h"),event_xmls);



    }

    if( true )//ios
    {


        QString event_xmls;


        event_xmls.append("#import \"FlowBoxs.h\"\n");

        event_xmls.append("@implementation FlowBoxs\n");

        event_xmls.append("+(NSString*) getBox:(Event)event{\n");


        event_xmls.append("        switch(event){\n");




        for(int i=0;i<business.count();i++)
        {

            MBusinessDelegate * mbd = business.at(i);

            View * view = mbd->viewgroup->getStart();

            if( view )
            {
                MProperty * mp = view-> getProperty("event");
                if( mp )
                {
                    MEventDelegate * me =   DP->getEventById(mp->p_value);
                    if( me )
                    {
                        event_xmls.append("         case ").append( me->event_name ).append(": return @\"").append(mbd->alia).append(".xml\";\n");

                    }
                }

            }

        }








        event_xmls.append("         } \n");
        event_xmls.append("         return nil; \n");
        event_xmls.append("} \n");

        event_xmls.append("@end \n");


        createFile(DATA_OUT_DIR("ios/FlowBoxs.m"),event_xmls);



    }



    return true;

}

bool D::createFile(const QString & path,const QString & strs)
{


    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {


        QTextStream out(&file);
        out<<strs;
        return true;

    }
    return false;

}

MData * D::getProjectInfo(const QString& key)
{


    for(MData * data : this->projectinfos)
    {
        if( data->key.compare( key ) == 0 )
            return data;
    }
    return NULL;

}


const QString  D::createCodes()
{



    /*
      *
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
     **/

    cleanGolableString();

    QString dirstr_android = DATA_OUT_DIR("java");
    QDir dir_android(dirstr_android);
    if( !dir_android.exists() )
        dir_android.mkpath(dirstr_android);

    QString dirstr_ios = DATA_OUT_DIR("ios");
    QDir dir_ios(dirstr_ios);
    if( !dir_ios.exists() )
        dir_ios.mkpath(dirstr_ios);




    QString strs;

    if( createEvent()  )
        strs.append("create event success.\n");
    else
        return "create event error";
    if( createModels()  )
        strs.append("create model success.\n");
    else
        return "create model error";
    if( createUrls()  )
        strs.append("create urls success.\n");
    else
        return "create urls error";

    if( createForms()  )
        strs.append("create form success.\n");
    else
        return "create form error";
    if( createBusiness()  )
        strs.append("create business success.\n");
    else
        return "create business error";
    createProjectInfos() ;
    strs.append("create project success.\n");
    if( createStrings() )
        strs.append("create Strings success.\n");

    return strs;

}
