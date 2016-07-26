#ifndef VIEWGROUP_H
#define VIEWGROUP_H
#include "view.h"




class ViewGroup:public View
{

public:
    QList<View*> m_children;

    View * m_focus_view;
    View * m_current_line;

public:

    ViewGroup();

    virtual ~ViewGroup();
    virtual void paint(QPaintEvent * event,QWidget * widget);
    virtual void paint(QPainter & painter,const QPalette & pal);
    virtual void paintChildren(QPaintEvent * event,QWidget * widget);
    View * getChildAt(int i);
    void setFocus(View * child);
    virtual void save(QXmlStreamWriter &writer);
    virtual void createCodes(QXmlStreamWriter &writer);
    virtual bool load(QXmlStreamReader &reader );


    View * getViewById(const QString & viewid);
    View * getStart();


public:

    virtual void setSize(int p_width,int p_height);
    virtual void setPos(int x,int y);
    virtual void requireLayout();
    virtual View * getViewAtPoint(const QPoint & p,bool rightbutton=false );
    void addView(View *view);

    void removeLines(View *view);
    void removeView(View *view);

    int getChildCount();
    View * getFocus();
    bool hasFocusView();
    void setCurrentLine(View * v);
    View * getCurrentLine();


};


#endif // VIEWGROUP_H
