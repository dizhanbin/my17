#include "viewgroup.h"



ViewGroup::ViewGroup():max_width(0),max_height(0){

m_focus_view = NULL;
m_current_line = NULL;
}

 ViewGroup::~ViewGroup(){

    //NLog::i("release ViewGroup ");


    while ( !m_children.isEmpty() )
       delete m_children.takeFirst();

    //NLog::i("release ViewGroup end.");
}

 void ViewGroup::paint(QPaintEvent * event,QWidget * widget)
{

    //  View::paint(event,widget);
    paintChildren(event,widget);

}
 void ViewGroup::paintChildren(QPaintEvent * event,QWidget * widget)
{

    View * focus = getFocus();
    for(View * view:m_children)
    {
        if( view != focus )
            view->paint(event,widget);
    }
    if( focus )
        focus->paint(event,widget);

}

 void ViewGroup::paint(QPainter & painter,const QPalette & pal)
 {
     //NLog::i("draw ViewGroup.paint ---------------");
     View * focus = getFocus();
     for(View * view:m_children)
     {
        // NLog::i("draw ViewGroup.paint....%s",view->getTypeName());



         if( view != focus )
             view->paint(painter,pal);
     }
     if( focus )
         focus->paint(painter,pal);


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

int viewgroup_max(int a,int b)
{
    return a>b?a:b;
}

void ViewGroup::addView(View *view)
{

   // view->setParent( this );
    m_children.push_back(view);


    this->max_width =viewgroup_max(this->max_width,view->getRect()->right());
    this->max_height =viewgroup_max(this->max_height,view->getRect()->bottom());


}
void ViewGroup::removeView(View *view)
{

    setFocus(NULL);
    m_children.removeOne(view);
    removeLines(view);


}

void ViewGroup::removeLines(View *view)
{

    if( !view->isLine() )
     for(int i=this->m_children.count()-1;i>-1;i-- )
     {
         View * v = m_children.at(i);

         if( v->isLine() && v->isLineTo(view) )
         {
                m_children.removeAt(i);
                delete v;
         }
     }

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
View * ViewGroup::getViewById(const QString & viewid)
{
    for(int i=0;i<this->m_children.count();i++)
    {
        View * view = m_children.at(i);
        if( view->viewid == viewid )
            return view;

    }
    return NULL;


}

View * ViewGroup::getStart()
{
    for(int i=0;i<this->m_children.count();i++)
    {

        View * view = m_children.at(i);
        if( !view->isLine() )
        {

            if( view->getElementid() == "001" )
            {

                return view;
            }

        }

    }
    return NULL;


}

void ViewGroup::createCodes(QXmlStreamWriter &writer)
{

    for(int i=0;i<this->m_children.count();i++ )
    {

        View * view = m_children.at(i);

        writer.writeStartElement( view->getCodeTag() );
        //const QString type = (view->getTypeName()+1);
        // writer.writeAttribute("type",type);

        view->createCodes(writer);
        writer.writeEndElement();
    }


}

void ViewGroup::save(QXmlStreamWriter &writer)
{
   // writer.writeStartElement("views");

    for(int i=0;i<this->m_children.count();i++ )
    {

        View * view = m_children.at(i);


        writer.writeStartElement( view->getXmlTag() );
        const QString type = (view->getTypeName()+1);
        writer.writeAttribute("type",type);

        view->save(writer);
        writer.writeEndElement();
    }


  //  writer.writeEndElement();

}


 bool ViewGroup::load(QXmlStreamReader &reader )
{

    return false;

}
