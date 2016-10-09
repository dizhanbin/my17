#include "lineview.h"

LineView::LineView():from(NULL),to(NULL),none(""){


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

void LineView::paint(QPainter & painter,const QPalette & pal)
{

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

            QPointF p0(from->getRect()->x()+from->getRect()->width()/2,from->getRect()->y()+from->getRect()->height()/2);
            QPointF p1(cursor.x(),cursor.y());
            painter.drawLine(p0,p1);
        }

    }

}
 void LineView::paint(QPaintEvent * event,QWidget * widget)
{

    QPainter painter(widget);
    const QPalette & pal = widget->palette();


    paint(painter,pal);





}

void LineView::drawArrow(QPainter & painter,float x1,float y1,float x2,float y2)
{

    float wh = 1.5;
    if( x1 == x2 )
    {
        x1 += wh;
        x2 = x1;
    }
    else if( y1 == y2 )
    {

        y1 += wh;
        y2 = y1;
    }



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


    float line_wh = 3;

    const QString & title = getDescript();


    int t_x,t_y;
    QFontMetricsF fontMetrics(painter.font());
    int text_w =  (int)fontMetrics.width(title);
    int text_h = 12;

    int ele_w = from->getRect()->width();
    int ele_h = from->getRect()->height();


    if( x0+ele_w/2 > x1 && x0+ele_w/2<x1+ele_w )//竖直方向
    {

        if( y1>y0)
        {
            int px0 = x0+ele_w/2;
            int py0 = y0+ele_h;

            int px1 = px0;
            int py1 = y1;
            painter.drawLine(px0,py0,px1,py1);
            drawArrow(painter,px0,py0,px1,py1);


            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );


            t_x = px0/2+px1/2;
            t_y = py0/2+py1/2;

        }
        else
        {


            int px0 = x0+ele_w/2;
            int py0 = y0;

            int px1 = px0;
            int py1 = y1+ele_h;
            painter.drawLine(px0,py0,px1,py1);
            drawArrow(painter,px0,py0,px1,py1);

            path.clear();
            path.append( QRect(px0,py0,px1-px0,py1-py0) );

            t_x = px0/2+px1/2;
            t_y = py0/2+py1/2;

        }



    }
    else if( x0+ele_w/2 > x1+ele_w  )//left 从上到左下
    {
        if( y0+ele_h/2>y1 && y0+ele_h/2<y1+ele_h)//
       {
           int px0 = x0;
           int py0 = y0+ele_h/2;

           int px1 = x1+ele_w;
           int py1 = py0;
           painter.drawLine(px0,py0,px1,py1);
           drawArrow(painter,px0,py0,px1,py1);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );

           t_x = px0/2+px1/2;
           t_y = py0/2+py1/2;


       }

       else if( y0+ele_h/2>y1+ele_h)
        {
            int px0 = x0+ele_w/2;
            int py0 = y0;

            int px1 = px0;
            int py1 = y1+ele_h/2;

            int px2 = x1+ele_w;
            int py2 = py1;

            painter.drawLine(px0,py0,px1,py1);
            painter.drawLine(px1,py1,px2,py2);

            drawArrow(painter,px1,py1,px2,py2);

            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );
            path.append(QRect(px1,py1,px2-px1,py2-py1) );


            t_x = px1/2+px2/2;

            t_y = py1-text_h;

        }


        else{

           int px0 = x0 + ele_w/2;
           int py0 = y0+ele_h;

           int px1 = px0;
           int py1 = y1+ele_h/2;

           int px2 = x1+ele_w;
           int py2 = py1;

           painter.drawLine(px0,py0,px1,py1);
           painter.drawLine(px1,py1,px2,py2);

           drawArrow(painter,px1,py1,px2,py2);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );
           path.append(QRect(px1,py1,px2-px1,py2-py1) );


           t_x = px1/2+px2/2;

           t_y = py1-text_h;

       }

    }
    else{//right


        if( y0+ele_h/2>y1 && y0+ele_h/2<y1+ele_h)
       {
           int px0 = x0+ele_w;
           int py0 = y0+ele_h/2;

           int px1 = x1;
           int py1 = py0;
           painter.drawLine(px0,py0,px1,py1);
           drawArrow(painter,px0,py0,px1,py1);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );


           t_x = px0/2+px1/2;

           t_y = py0-text_h;

       }

       else if( y0+ele_h/2>y1+ele_h)  //right north
        {
            int px0 = x0+ele_w/2;
            int py0 = y0;

            int px1 = px0;//x1+ele_w/2;
            int py1 = y1+ele_h/2;

            int px2 =  x1;
            int py2 =  py1;

            painter.drawLine(px0,py0,px1,py1);
            painter.drawLine(px1,py1,px2,py2);

            drawArrow(painter,px1,py1,px2,py2);

            path.clear();
            path.append(QRect(px0,py0,px1-px0,py1-py0) );
            path.append(QRect(px1,py1,px2-px1,py2-py1) );

            t_x = px1/2+px2/2;

            t_y = py1-text_h;


        }


        else{

           int px0 = x0+ele_w/2;
           int py0 = y0+ele_h;

           int px1 = px0;
           int py1 = y1+ele_h/2;

           int px2 = x1;
           int py2 = py1;

           painter.drawLine(px0,py0,px1,py1);
           painter.drawLine(px1,py1,px2,py2);

           drawArrow(painter,px1,py1,px2,py2);

           path.clear();
           path.append(QRect(px0,py0,px1-px0,py1-py0) );
           path.append(QRect(px1,py1,px2-px1,py2-py1) );

           t_x = px1/2+px2/2;

           t_y = py1-text_h;


       }




    }






    painter.drawText(t_x-text_w/2,t_y,title );




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

 bool LineView::isLineTo(View *v)
 {
     return ( v && (v==from || v== to));
 }


 QString   LineView::getCodeTag()
 {

     return "Line";

 }

 void LineView::createCodes(QXmlStreamWriter &writer)
 {

     writer.writeTextElement("id",viewid);
     writer.writeTextElement("from", from->viewid );
     writer.writeTextElement("to", to->viewid );





     MProperty * mpc = getProperty("condition");
     if( mpc )
        writer.writeTextElement("condition", mpc->p_value );

     MProperty * mp = getProperty("isint");
     if( mp )
        writer.writeTextElement("isint", mp->p_value );


 }


 void LineView::save(QXmlStreamWriter &writer)
 {

    writer.writeTextElement("id",viewid);

    writer.writeTextElement("x",QString::number( m_rect.x() ) );
    writer.writeTextElement("y",QString::number( m_rect.y() ) );
    writer.writeTextElement("w",QString::number( m_rect.width() ) );
    writer.writeTextElement("h",QString::number( m_rect.height() ) );

    writer.writeTextElement("from", from->viewid );
    writer.writeTextElement("to", to->viewid );


    saveData(writer,"linedata");
    //saveData(writer,"isint");

 }


 bool LineView::load(QXmlStreamReader &reader )
 {


     int x,y,w,h;
     while( true )
     {

          reader.readNext();
          QStringRef  name = reader.name();

         // NLog::i("LineView tag:"+name.toString());

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
             else if( name == "from" )
                 fromid = reader.readElementText();
             else if( name == "to" )
                 toid = reader.readElementText();
             else if( name == "linedata" )
             {
                 loadData(reader);
                 MProperty * mpisint = getProperty("isint");
                 if( !mpisint )
                 {
                     MProperty * mp_int = new MProperty();
                     mp_int->p_name = "isint";
                     mp_int->p_title = "数字";
                     mp_int->p_type = 1;
                     mp_int->p_args = "$boolean";
                     this->properties.append(mp_int);
                 }
             }
            // else if( name == "isint" )
            //     isint = reader.readElementText();

         }
         else if( reader.isEndElement() )
         {


             if( name == "view" || name == "Line")
                 return true;

         }

     }


      return false;

 }

  void LineView::line(View *from,View * to)
  {


      this->from = from;
      this->to = to;

  }

    QString LineView::getXmlTag(){

       return "Line";
   }

    void LineView::setDefProperty()
    {
        MProperty * mp = new MProperty();

        mp->p_name = "condition";
        mp->p_title = "条件";
        mp->p_type = 0;
      this->properties.append(mp);

        MProperty * mp_int = new MProperty();
        mp_int->p_name = "isint";
        mp_int->p_title = "数字";
        mp_int->p_type = 1;
        mp_int->p_args = "$boolean";
        this->properties.append(mp_int);


    }
   const  QString &  LineView::getDescript()
    {

        MProperty * mp = getProperty("condition");

        if( mp )
            return mp->p_value;
        else
            return none;

    }
