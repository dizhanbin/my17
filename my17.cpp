#include "my17.h"
#include <qxmlstream.h>
#include "viewgroup.h"
#include "iconview.h"
#include "lineview.h"
#include "mproperty.h"

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
                 med->viewgroup->addView(view);
                if( !  view->load(reader) )
                {
                    NLog::i("read type:%s error",type.toStdString().c_str());
                    return ;
                }

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


     QString strs = "/* create my 17 */\n";
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


     QFile file(DATA_OUT_DIR("Event.java"));
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return false;
     QTextStream out(&file);
     out<<strs;


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


     QFile file(DATA_OUT_DIR("Urls.java"));
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return false;
     QTextStream out(&file);
     out<<strs;


     return true;
 }


 bool d_create_form_code(MForm * form)
 {



     QString strs = "/* create my 17 */\n";


     MProperty * formp = RP->getPropertyByName(form->properties,"android");


     if( !formp )
         return false;

     strs.append("public class ").append(formp->p_value).append("  extends Form{\n\n");




     strs.append("\n}\n");

     QString filename = DATA_OUT_DIR("");
     filename.append( formp->p_value).append(".java");

     QFile file(filename);

     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return false;
     QTextStream out(&file);
     out<<strs;


     return true;
 }

 bool D::createForms()
 {


     QString strs = "/* create my 17 */\n";

     strs.append("public class FormFactory{\n");
     strs.append("  public static Class getForm(Event event){\n");
     strs.append("      switch(event){\n");


     for(int i=0;i<forms.count();i++)
     {

         MForm * form = forms.at(i);


         const QString & str_event = RP->getPropertyByName(form->properties,"event")->p_value;
         const QString & str_android = RP->getPropertyByName(form->properties,"android")->p_value;

         MEventDelegate * me =  DP->getEventById( str_event );


         strs.append("          case Event.").append(me->event_name).append(": return ")
                 .append(  str_android  ).append(".class;\n");

         d_create_form_code(form);

     }

     strs.append("          }\n");
     strs.append("      return null;\n");
     strs.append("  }\n");
     strs.append("}\n");



     QString filename = DATA_OUT_DIR("");
     filename.append("FormFactory.java");

     QFile file(filename);

     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return false;
     QTextStream out(&file);
     out<<strs;


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
         mbd->viewgroup->createCodes(writer);
         writer.writeEndElement();
         writer.writeEndDocument();
         file.close();


     }




 }

 bool  createModel( MModelDelegate * md)
 {

     QString path = DATA_OUT_DIR("");
     path.append(md->name).append(".java");


     QString strs = "/* create my 17 */\n";
     strs.append("public class ").append(md->name).append("{\n\n");


     for(int i=0;i<md->fields.count();i++)
     {
         MModelFieldDelegate * field = md->fields.at(i);

         strs.append("  public ").
                 append( RP->model_field_type_index(field->field_type) ).
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
         return true;

     }



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


 bool D::createBusiness()
 {





     QString event_xmls;
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



     createFile(DATA_OUT_DIR("FlowBoxs.java"),event_xmls);


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
     QString dirstr = DATA_OUT_DIR("");


     QDir dir(dirstr);
     if( !dir.exists() )
        dir.mkpath(dirstr);


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

    return strs;

 }
