#include "lineview.h"

LineView::LineView():from(NULL),to(NULL){


}


void LineView::setFrom(View *fv)
{
    from = fv;
    setTo(from->getRect()->x()+from->getRect()->width()/2,from->getRect()->y()+from->getRect()->height()/2);
}
void LineView::setTo(View * tv)
{

    to = tv;

}

void LineView::setTo(int x,int y)
{
    cursor.setX(x);
    cursor.setY(y);

}

 void LineView::paint(QPaintEvent * event,QWidget * widget)
{

    QPainter painter(widget);
    const QPalette & pal = widget->palette();

    QColor color =   m_isfocus ? QColor(0xff,0,0) : QColor(0,0,0xff);


    QPen pen = QPen( color );
    pen.setWidth(3);
    painter.setPen(pen);


    painter.setBrush( QBrush( color, Qt::SolidPattern ) );

    if( from  )
    {

        if( to )
        {

            int x0 = from->getRect()->x();
            int y0 = from->getRect()->y();

            int x1 = to->getRect()->x();
            int y1 = to->getRect()->y();

            drawLine(painter,x0,y0,x1,y1);

        }
        else
        {

            QPointF p0(from->getRect()->x()+getRect()->width()/2,from->getRect()->y()+getRect()->height()/2);
            QPointF p1(cursor.x(),cursor.y());
            painter.drawLine(p0,p1);
        }

    }



}

void LineView::drawArrow(QPainter & painter,float x1,float y1,float x2,float y2)
{

    float l = 10.0;                   //箭头的那长度

    float a = 0.5;                       //箭头与线段角度

    float x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);

    float y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);

    float x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);

    float y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);

    painter.drawLine(x2,y2,x3,y3);

    painter.drawLine(x2,y2,x4,y4);

    painter.drawLine(x1,y1,x2,y2);


}


void LineView::drawLine(QPainter & painter,int x0,int y0,int x1,int y1)
{

    if( x0+ELE_WH/2 > x1 && x0+ELE_WH/2<x1+ELE_WH )
    {

        if( y1>y0)
        {
            int px0 = x0+ELE_WH/2;
            int py0 = y0+ELE_WH;

            int px1 = px0;
            int py1 = y1;
            painter.drawLine(px0,py0,px1,py1);
            drawArrow(painter,px0,py0,px1,py1);


            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );


        }
        else
        {


            int px0 = x0+ELE_WH/2;
            int py0 = y0;

            int px1 = px0;
            int py1 = y1+ELE_WH;
            painter.drawLine(px0,py0,px1,py1);
            drawArrow(painter,px0,py0,px1,py1);

            path.clear();
            path.append( QRect(px0,py0,px1-px0,py1-py0) );

        }


    }
    else if( x0+ELE_WH/2 > x1+ELE_WH  )//left
    {
        if( y0+ELE_WH/2>y1 && y0+ELE_WH/2<y1+ELE_WH)
       {
           int px0 = x0;
           int py0 = y0+ELE_WH/2;

           int px1 = x1+ELE_WH;
           int py1 = py0;
           painter.drawLine(px0,py0,px1,py1);
           drawArrow(painter,px0,py0,px1,py1);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );
       }

       else if( y0+ELE_WH/2>y1+ELE_WH)
        {
            int px0 = x0+ELE_WH/2;
            int py0 = y0;

            int px1 = px0;
            int py1 = y1+ELE_WH/2;

            int px2 = x1+ELE_WH;
            int py2 = py1;

            painter.drawLine(px0,py0,px1,py1);
            painter.drawLine(px1,py1,px2,py2);

            drawArrow(painter,px1,py1,px2,py2);

            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );
            path.append(QRect(px1,py1,px2-px1,py2-py1) );
        }


        else{

           int px0 = x0;
           int py0 = y0+ELE_WH/2;

           int px1 = x1+ELE_WH/2;
           int py1 = py0;

           int px2 = px1;
           int py2 = y1;

           painter.drawLine(px0,py0,px1,py1);
           painter.drawLine(px1,py1,px2,py2);

           drawArrow(painter,px1,py1,px2,py2);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );
           path.append(QRect(px1,py1,px2-px1,py2-py1) );

       }

    }
    else{//right


        if( y0+ELE_WH/2>y1 && y0+ELE_WH/2<y1+ELE_WH)
       {
           int px0 = x0+ELE_WH;
           int py0 = y0+ELE_WH/2;

           int px1 = x1;
           int py1 = py0;
           painter.drawLine(px0,py0,px1,py1);
           drawArrow(painter,px0,py0,px1,py1);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );


       }

       else if( y0+ELE_WH/2>y1+ELE_WH)  //right north
        {
            int px0 = x0+ELE_WH/2;
            int py0 = y0;

            int px1 = px0;//x1+ELE_WH/2;
            int py1 = y1+ELE_WH/2;

            int px2 =  x1;
            int py2 =  py1;

            painter.drawLine(px0,py0,px1,py1);
            painter.drawLine(px1,py1,px2,py2);

            drawArrow(painter,px1,py1,px2,py2);

            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );
            path.append(QRect(px1,py1,px2-px1,py2-py1) );
        }


        else{

           int px0 = x0+ELE_WH/2;
           int py0 = y0+ELE_WH;

           int px1 = px0;
           int py1 = y1+ELE_WH/2;

           int px2 = x1;
           int py2 = py1;

           painter.drawLine(px0,py0,px1,py1);
           painter.drawLine(px1,py1,px2,py2);

           drawArrow(painter,px1,py1,px2,py2);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );
           path.append(QRect(px1,py1,px2-px1,py2-py1) );

       }




    }





}


 bool LineView::isPointIn(const QPoint &p)
{

    for(int i=0;i<path.size();i++)
    {

        QRect  rect = path.at(i);

        int left = min(rect.left(),rect.right());
        int top = min(rect.top(),rect.bottom());
        int right = max(rect.left(),rect.right());
        int bottom = max(rect.top(),rect.bottom());

        int off = 4;
        if(  ( left-off <= p.x() && right+off >= p.x()
             && top-off <= p.y() && bottom+off >= p.y() ) )
          return true;
    }

}


 bool LineView::isLine()
{

    return true;
}
