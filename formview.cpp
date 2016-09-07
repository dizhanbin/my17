#include "formview.h"

FormView::FormView()
{


    m_bitmap =  new QPixmap(":/image/form.png");
}

void FormView::initFormData()
{
    this->setSize(form->w,form->h);
    this->setPos(form->x,form->y);


}

void FormView::paint(QPainter & painter,const QPalette & pal)
{
    QRect drawrect = m_rect;
    if( m_isfocus )
    {

        int off = 2;
        QPen pen = QPen( pal.toolTipBase().color() );
        pen.setWidth(off);

        painter.setPen(pen);
        painter.setBrush( QBrush(pal.toolTipBase().color(),Qt::SolidPattern ) );
        painter.drawRect(drawrect);
    }


    if( m_bitmap )
        painter.drawPixmap(drawrect, *m_bitmap);

    if( this->m_isfocus )
    {
        QPen pen = QPen( QColor( 0xff,0,0 ) );
        painter.setPen(pen);
    }
    else
    {

        QPen pen = QPen( QColor( 0,0,0 ) );
        painter.setPen(pen);

    }

    const QString &title = getDescript();
    QFontMetricsF fontMetrics(painter.font());
    int text_w =  (int)fontMetrics.width(title);


    painter.drawText(drawrect.x()+(drawrect.width() - text_w)/2,drawrect.y(), title );

}

const QString & FormView::getDescript()
{

    for(int i=0;i<form->properties.size();i++)
    {
       MProperty * mp = form->properties.at(i);
       if( mp->p_name ==  "descript" )
       {
           return mp->p_value;
       }

    }
    return "";
}

void  FormView::setPos(int x,int y)
{

    View::setPos(x,y);
    if( form ){
        form->x = x;
        form->y = y;
    }

}

