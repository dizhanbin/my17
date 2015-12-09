#include "my17.h"
#include <qxmlstream.h>
#include "viewgroup.h"
#include "iconview.h"
#include "lineview.h"
using namespace my17;

static R* s_r_instance = NULL;
static D* s_d_instance = NULL;

R* R::getInstance()
{

    if( s_r_instance == NULL )
        s_r_instance = new R();
    return s_r_instance;

}



D* D::getInstance()
{

    if( s_d_instance == NULL )
        s_d_instance = new D();
    return s_d_instance;

}

void D::loadModel()
{

    QFile file("/Users/dzb/models.xml");
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

    QFile file("/Users/dzb/models.xml");
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

    QFile file("/Users/dzb/events.xml");
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
 QFile file("/Users/dzb/events.xml");
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

    QFile file("/Users/dzb/business.xml");
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


    QFile file("/Users/dzb/business.xml");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader reader(&file);
        reader.readNext();

        MBusinessDelegate * med = NULL;
        View * view = NULL;

        while( !reader.atEnd() )
        {
            QStringRef  name = reader.name();
            if( reader.isStartElement() )
            {
              if( name == "item" )
              {


                    med = newBusiness();
                    med->name = reader.attributes().value("name").toString();
                    if( reader.attributes().hasAttribute("type") )
                        med->type = reader.attributes().value("type").toInt();
                    else
                        med->type = 1;

              }
              else if( name == "view" )
              {
                 QString type = reader.attributes().value("type").toString();
                 View * view = createView(type );
                 med->viewgroup->addView(view);
                if( !  view->load(reader) )
                {
                    NLog::i("read type:%s error",type.toStdString().c_str());
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


bool D::saveUrl()
{

    QFile file("/Users/dzb/urls.xml");
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



    QFile file("/Users/dzb/urls.xml");
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
            else if( reader.isEndElement() )
            {



            }



            reader.readNext();
        }

         file.close();

    }




}
