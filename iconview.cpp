#include "iconview.h"
#include "my17.h"

IconView::IconView()
{

    m_bitmap = NULL;

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
    else if( hasGlobalVar ){

        int off = m_isfocus ? 3 : 2;
        QPen pen = QPen( QColor::fromRgb(0xff,0x00,0xff,0x55) );
        pen.setWidth(off);
        painter.setPen(pen);
        painter.setBrush( QBrush( QColor::fromRgb(0xff,0x00,0xff,0x55) ,Qt::SolidPattern ) );
        painter.drawRect(drawrect);

    }
    if( !m_bitmap )
    {
        const MElement * ele =  my17::R::getInstance()->getElement(m_element_id);

        if( ele ){

            if( ele->iconpath.startsWith("./") ){
                QString path = DATA_DIR("").append(ele->iconpath);
                m_bitmap = new QPixmap(path);
            }
            else
                m_bitmap = new QPixmap(ele->iconpath);
        }

    }
    if( m_bitmap )
        painter.drawPixmap(drawrect, *m_bitmap);


    const QString & title = getDescript();
    if( title.length() > 0  )
    {
        if( m_isfocus )
        {
            QPen pen = QPen( QColor( 0xff,0,0 ) );

            painter.setPen(pen);
        }
        QFontMetricsF fontMetrics(painter.font());

        int strwidth = (int)fontMetrics.width(title);
        QPointF p( drawrect.x()+(drawrect.width() - strwidth)/2,drawrect.y()-painter.font().pixelSize() );
        painter.drawText( p,title );//,QTextOption(Qt::AlignCenter) );
    }
}

  QString  IconView::getCodeTag()
{

    return "item";

}

IconView * IconView::copy()
{


    IconView * icon = new IconView();

    //memcpy(icon,this,sizeof(IconView));
    icon->m_element_id = m_element_id;
    icon->m_bitmap = NULL;
    icon->m_rect = m_rect;
    //icon->m_rect.moveLeft();
    icon->m_rect.moveTo( QPoint(m_rect.left()+m_rect.width()/2,m_rect.top()+m_rect.height()/2) );

    icon->newProperties(properties);
    icon->viewid = RP->getId();



    return icon;


}

void IconView::createCodes(QXmlStreamWriter &writer)
{

   NLog::i("createCodes : before");

    writer.writeAttribute("id",viewid);

    const MElement * ele = RP->getElement(m_element_id);


    NLog::i("element :%s",ele->name.toStdString().c_str() );

    writer.writeAttribute("c_android",ele->c_android);

    writer.writeAttribute("c_ios",ele->c_ios);


    NLog::i("c_android : %s",ele->c_android.toStdString().c_str());

    //writer.writeTextElement("id",viewid);
    //writer.writeTextElement("elementid",m_element_id);
    //RP->getElement(m_element_id)->

    createProprityCodes(writer,"data");

}

void IconView::save(QXmlStreamWriter &writer)
{


    writer.writeTextElement("id",viewid);
    writer.writeTextElement("x",QString::number( m_rect.x() ) );
    writer.writeTextElement("y",QString::number( m_rect.y() ) );
    writer.writeTextElement("w",QString::number( m_rect.width() ) );
    writer.writeTextElement("h",QString::number( m_rect.height() ) );
    writer.writeTextElement("elementid",m_element_id);
    saveData(writer,"data");

}

 const QString & IconView::getTopDescript()
{



    return my17::R::getInstance()->getElement( m_element_id )->descript;
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
            else if( name == "elementid" )
                m_element_id = reader.readElementText();
            else if( name == "data" )
                loadData(reader);
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
