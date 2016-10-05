#include "view.h"



View::View():m_isfocus(false),m_rect(30,30,ELE_W_H,ELE_W_H)
{
    viewid = RP->getId();
}

 View::~View()
{

    while(!properties.isEmpty())
    {

        delete properties.takeAt(0);

    }
}

 void View::paint(QPainter & painter,const QPalette & pal)
 {

     NLog::i("draw in view.cpp ...24");

     QRect drawrect = m_rect;

     int off = m_isfocus ? 3 : 2;

     QPen pen = pal.toolTipBase().color();
     pen.setWidth(off);
     painter.setPen(pen);
     painter.setBrush( QBrush(QColor(0x51,0x8e,0xd8,0x88 ),Qt::SolidPattern ) );

     drawrect.adjust(off,off,-off,-off);

     painter.drawRect(drawrect);

 }

void View::paint(QPaintEvent * event,QWidget * widget)
{

        QPainter painter(widget);
        const QPalette & pal = widget->palette();

        paint(painter,pal);

}




void  View::setSize(int p_width,int p_height)
{
    m_rect.setSize(QSize(p_width,p_height));
}
 void  View::setPos(int x,int y)
{
    m_rect.setRect(x,y,m_rect.width(),m_rect.height());
}


int  View::max(int a,int b)
{
    return a>b?a:b;
}
 int  View::min(int a,int b)
{

    return a>b?b:a;
}


 bool  View::isLine()
{

    return false;
}

  bool View::isLineTo(View *v)
 {

     return false;
 }

bool View::isRoot()
 {

     return isroot;

 }
void View::setRoot(bool is)
{

    isroot = is;

}

 bool  View::isPointIn(const QPoint &p)
{
    NLog::i("view l,t,r,b:%d,%d,%d,%d",m_rect.left(),m_rect.top(),m_rect.right(),m_rect.bottom());

    return ( m_rect.left() < p.x() && m_rect.right() > p.x()
             && m_rect.top() < p.y() && m_rect.bottom() > p.y() );

}
 QRect * View::getRect()
{

    return &m_rect;
}

 void  View::setFocus(bool focus)
 {

     m_isfocus = focus;
 }

 void View::createCodes(QXmlStreamWriter &writer)
 {
      NLog::i("createCodes not implements....");
 }

  void  View::save(QXmlStreamWriter &writer)
  {
      NLog::i("not implements....");


  }



   void View::createProprityCodes(QXmlStreamWriter &writer,const QString & tag)
   {

       writer.writeStartElement(tag);

       for(int i=0;i<properties.count();i++)
       {

           MProperty * p = properties.at(i);


           NLog::i("code: property :%s",p->p_name.toStdString().c_str());

           writer.writeStartElement("property");
           writer.writeAttribute("name",p->p_name);
           writer.writeAttribute("title",p->p_title);

           if( p->p_type == 1  )
           {



               writer.writeAttribute("value",DP->getPropertyValue(p->p_args,p->p_value));
           }
           else
           {
               writer.writeAttribute("value",p->p_value);

           }

           writer.writeEndElement();

       }
       writer.writeEndElement();

   }

  void View::saveData(QXmlStreamWriter &writer,const QString & tag)
  {
      writer.writeStartElement(tag);

      for(int i=0;i<properties.count();i++)
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


  }

  bool View::loadData(QXmlStreamReader &reader )
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

  bool View::load(QXmlStreamReader &reader )
  {
       NLog::i("not implements....");

  }


   void View::newProperties(QList<MProperty*> ps)
   {


        for(int i=0;i<ps.count();i++)
        {

            this->properties.push_back( ps.at(i)->copy() );
        }


   }

   const QString & View::getTopDescript()
   {

       return " ";
   }

   MProperty * View:: getProperty(const QString & name)
   {

       for(int i=0;i<this->properties.size();i++)
       {
          MProperty * mp = properties.at(i);
          if( mp->p_name ==  name )
          {
              return mp;
          }

       }
       return NULL;

   }


   const QString & View::getDescript()
   {

       for(int i=0;i<this->properties.size();i++)
       {
          MProperty * mp = properties.at(i);
          if( mp->p_name ==  "descript" )
          {
              return mp->p_value;
          }

       }
       return "";
   }

    QString  View::getXmlTag()
   {

       return "view";
   }

     QString  View::getCodeTag()
   {
       return "view";

   }


///////////////////viewgroup
///
///
///

