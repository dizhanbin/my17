#include "iconview.h"


IconView::IconView()
{

    m_bitmap = NULL;

}

void IconView::setImage(const QString & imagepath)
{

    m_bitmap = new QPixmap(imagepath);
    m_iconpath = imagepath;
}

    IconView::IconView(const QString & imagepath)
    {

        setImage(imagepath);

    }

     IconView::~IconView(){

        if( m_bitmap )
            delete m_bitmap;

    }

     void  IconView::paint(QPaintEvent * event,QWidget * widget)
    {

        QPainter painter(widget);
        const QPalette & pal = widget->palette();

        QRect drawrect = m_rect;
        if( m_isfocus )
        {

            int off = m_isfocus ? 3 : 2;
            QPen pen = QPen( pal.toolTipBase().color() );
            pen.setWidth(off);
            painter.setPen(pen);
            painter.setBrush( QBrush(pal.toolTipBase().color(),Qt::SolidPattern ) );
            painter.drawRect(drawrect);
        }
        if( !m_bitmap && m_iconpath.length()>0 )
        {
            m_bitmap = new QPixmap(m_iconpath);

        }
        if( m_bitmap )
            painter.drawPixmap(drawrect, *m_bitmap);
    }


     void IconView::save(QXmlStreamWriter &writer)
     {


        writer.writeTextElement("id",viewid);
        writer.writeTextElement("x",QString::number( m_rect.x() ) );
        writer.writeTextElement("y",QString::number( m_rect.y() ) );
        writer.writeTextElement("w",QString::number( m_rect.width() ) );
        writer.writeTextElement("h",QString::number( m_rect.height() ) );
        writer.writeTextElement("iconpath",m_iconpath);


     }

 bool IconView::load(QXmlStreamReader &reader )
     {

        int x,y,w,h;
        while( true )
        {

             reader.readNext();
             QStringRef  name = reader.name();
             if( reader.isStartElement() )
             {

                if( name == "id" )
                    viewid = reader.readElementText();
                else if( name == "x" )
                    x = reader.readElementText().toInt();
                else if( name == "y" )
                    y = reader.readElementText().toInt();
                else if( name == "w" )
                    w = reader.readElementText().toInt();
                else if( name == "h" )
                    h = reader.readElementText().toInt();
                else if( name == "iconpath" )
                    m_iconpath = reader.readElementText();
            }
            else if( reader.isEndElement() )
            {


                if( name == "view" )
                {
                    m_rect.setLeft(x);
                    m_rect.setTop(y);
                    m_rect.setWidth(w);
                    m_rect.setHeight(h);

                    return true;
                }

            }

        }


         return false;

     }
