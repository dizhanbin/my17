#include "my17.h"
#include <qxmlstream.h>
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
