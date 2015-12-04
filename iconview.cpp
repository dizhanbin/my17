#include "iconview.h"


    IconView::IconView(const QString & imagepath)
    {
      m_bitmap = new QPixmap(imagepath);

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
        painter.drawPixmap(drawrect, *m_bitmap);
    }
