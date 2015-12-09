#include "view.h"



View::View():m_isfocus(false),m_rect(30,30,ELE_W_H,ELE_W_H)
{
    viewid = RP->getId();
}


void View::paint(QPaintEvent * event,QWidget * widget)
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

  void  View::save(QXmlStreamWriter &writer)
  {


      NLog::i("not implements....");

  }

  bool View::load(QXmlStreamReader &reader )
  {
       NLog::i("not implements....");

  }


   void View::newProperties(QList<MProperty*> ps)
   {



   }

///////////////////viewgroup
///
///
///

