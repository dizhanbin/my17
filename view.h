#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include "nlog.h"
#include <qxmlstream.h>
#include <math.h>


#define ELE_WH  36
#define ELE_W_H  40


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


    inline int max(int a,int b)
    {
        return a>b?a:b;
    }
    inline int min(int a,int b)
    {

        return a>b?b:a;
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

     void setFocus(bool focus)
     {

         m_isfocus = focus;
     }

     virtual void save(QXmlStreamWriter &writer){};

protected:
    QRect m_rect;



    bool m_isfocus;



};






#endif // VIEW_H
