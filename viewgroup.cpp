#include "viewgroup.h"



ViewGroup::ViewGroup(){



}

 ViewGroup::~ViewGroup(){

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

 void ViewGroup::paint(QPaintEvent * event,QWidget * widget)
{

    //  View::paint(event,widget);
    paintChildren(event,widget);

}
 void ViewGroup::paintChildren(QPaintEvent * event,QWidget * widget)
{

    for(View * view:m_children)
        view->paint(event,widget);

}

View * ViewGroup::getChildAt(int i)
{
    return m_children.at(i);

}
void ViewGroup::setFocus(View * child)
{

    if( m_focus_view )
        m_focus_view->setFocus(false);
    m_focus_view = child;
    if( m_focus_view )
        m_focus_view->setFocus(true);
}



 void ViewGroup::setSize(int p_width,int p_height)
{

    this->m_rect.setWidth(p_width);
    this->m_rect.setHeight(p_height);
}

 void ViewGroup::setPos(int x,int y)
{

    View::setPos(x,y);
    /*
    for(int i=0;i<m_children.size();i++)
    {

        m_children.at(i)->setPos(x,y);

    }
    */
}

 void ViewGroup::requireLayout()
{
    setSize(getRect()->width(),getRect()->height());
    setPos(getRect()->x(),getRect()->y());
}


 View * ViewGroup::getViewAtPoint(const QPoint & p,bool rightbutton )
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
void ViewGroup::addView(View *view)
{

   // view->setParent( this );
    m_children.push_back(view);


}
void ViewGroup::removeView(View *view)
{

    m_children.removeOne(view);

}


int ViewGroup::getChildCount()
{

    return m_children.size();

}


View * ViewGroup::getFocus()
{

    return m_focus_view;

}
bool ViewGroup::hasFocusView()
{

    return m_focus_view;

}
void ViewGroup::setCurrentLine(View * v)
{

    m_current_line = v;

}
View * ViewGroup::getCurrentLine()
{

    return m_current_line;

}
