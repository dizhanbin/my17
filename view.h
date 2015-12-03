#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include "nlog.h"

#include <math.h>


#define ELE_WH  36
#define ELE_W_H  40


class ViewGroup;

class View
{
public:
    int off_width,off_height;
public:

    View():m_isfocus(false),m_rect(30,30,ELE_W_H,ELE_W_H)
    {


    }



    virtual void paint(QPaintEvent * event,QWidget * widget)
    {

        QPainter painter(widget);
        const QPalette & pal = widget->palette();

        QRect drawrect = m_rect;

        int off = m_isfocus ? 3 : 2;

        QPen pen = pal.toolTipBase().color();
        pen.setWidth(off);
        painter.setPen(pen);
        painter.setBrush( QBrush(QColor(0x51,0x8e,0xd8,0x88 ),Qt::SolidPattern ) );

        drawrect.adjust(off,off,-off,-off);

        painter.drawRect(drawrect);

    }

public:
    virtual void setSize(int p_width,int p_height)
    {
        //m_rect.setRect(0,0,p_width,p_height);
        //m_rect.adjust(0,0,p_width,p_height);
        m_rect.setSize(QSize(p_width,p_height));
    }
    virtual void setPos(int x,int y)
    {
        m_rect.setRect(x,y,m_rect.width(),m_rect.height());
    }
    ViewGroup * getParent()
    {

        return m_parent;

    }


    virtual bool isLine()
    {

        return false;
    }



    virtual bool isPointIn(const QPoint &p)
    {
        NLog::i("view l,t,r,b:%d,%d,%d,%d",m_rect.left(),m_rect.top(),m_rect.right(),m_rect.bottom());

        return ( m_rect.left() < p.x() && m_rect.right() > p.x()
                 && m_rect.top() < p.y() && m_rect.bottom() > p.y() );

    }
     QRect *getRect()
    {

        return &m_rect;
    }
     void setParent(ViewGroup * p)
     {

         m_parent = p;
     }

     void setFocus(bool focus)
     {

         m_isfocus = focus;
     }

protected:
    QRect m_rect;

    ViewGroup * m_parent;



    bool m_isfocus;



};

class LineView;
class IconView;


class ViewGroup : public View
{

protected:
    QList<View*> m_children;

    View * m_focus_view;
    View * m_current_line;
public:

    ViewGroup(){



    };

    virtual ~ViewGroup(){

        NLog::i("release ViewGroup ");
        while(m_children.size()>0)
            /*
        {
           View * view = m_children.at(m_children.size()-1);
           m_children.removeAt(m_children.size()-1);
           delete view;
        }
            */
        while ( !m_children.isEmpty() )
           delete m_children.takeFirst();

        NLog::i("release ViewGroup end.");
    }

    virtual void paint(QPaintEvent * event,QWidget * widget)
    {

        //  View::paint(event,widget);
        paintChildren(event,widget);

    }
    virtual void paintChildren(QPaintEvent * event,QWidget * widget)
    {

        for(View * view:m_children)
            view->paint(event,widget);

    }

    View * getChildAt(int i)
    {
        return m_children.at(i);

    }
    void setFocus(View * child)
    {

        if( m_focus_view )
            m_focus_view->setFocus(false);
        m_focus_view = child;
        if( m_focus_view )
            m_focus_view->setFocus(true);
    }

public:


    virtual void setSize(int p_width,int p_height)
    {

        this->m_rect.setWidth(p_width);
        this->m_rect.setHeight(p_height);
    }

    virtual void setPos(int x,int y)
    {

        View::setPos(x,y);
        /*
        for(int i=0;i<m_children.size();i++)
        {

            m_children.at(i)->setPos(x,y);

        }
        */
    }

    virtual void requireLayout()
    {
        setSize(getRect()->width(),getRect()->height());
        setPos(getRect()->x(),getRect()->y());
    }


    virtual View * getViewAtPoint(const QPoint & p,bool rightbutton=false )
    {


        for(int i=m_children.count()-1;i>-1;i--)
        {
            View * v = m_children.at(i);
            if( v->isPointIn(p)  )
            {
                if(rightbutton && strstr(typeid(*v).name(),"LineView")  )
                    continue;
                return v;
            }
        }

        return NULL;

    }
    void addView(View *view)
    {

        view->setParent( this );
        m_children.push_back(view);


    }
    void removeView(View *view)
    {

        m_children.removeOne(view);

    }


    int getChildCount()
    {

        return m_children.size();

    }


    View * getFocus()
    {

        return m_focus_view;

    }
    bool hasFocusView()
    {

        return m_focus_view;

    }
    void setCurrentLine(View * v)
    {

        m_current_line = v;

    }
    View * getCurrentLine()
    {

        return m_current_line;

    }

};



class IconView :public View
{

 public:
    QPixmap * m_bitmap;

 public:
    IconView(const QString & imagepath)
    {
      m_bitmap = new QPixmap(imagepath);

    }

    ~IconView(){

        if( m_bitmap )
            delete m_bitmap;

    }

    virtual void paint(QPaintEvent * event,QWidget * widget)
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

};

class LineView : public View
{

private:
    View * from;
    View * to;

    QPoint cursor;

    QList<QRect> path;

public:
    LineView():from(NULL),to(NULL){


    }


    void setFrom(View *fv)
    {
        from = fv;
        setTo(from->getRect()->x()+from->getRect()->width()/2,from->getRect()->y()+from->getRect()->height()/2);
    }
    void setTo(View * tv)
    {

        to = tv;

    }

    void setTo(int x,int y)
    {
        cursor.setX(x);
        cursor.setY(y);

    }

    virtual void paint(QPaintEvent * event,QWidget * widget)
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

    void drawArrow(QPainter & painter,float x1,float y1,float x2,float y2)
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


    void drawLine(QPainter & painter,int x0,int y0,int x1,int y1)
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

    inline int max(int a,int b)
    {
        return a>b?a:b;
    }
    inline int min(int a,int b)
    {

        return a>b?b:a;
    }

    virtual bool isPointIn(const QPoint &p)
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


    virtual bool isLine()
    {

        return true;
    }



};


#endif // VIEW_H
