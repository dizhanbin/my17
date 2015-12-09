#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include "nlog.h"
#include <qxmlstream.h>
#include <math.h>
#include "my17.h"

#define ELE_WH  36
#define ELE_W_H  40




class View
{
public:

    int off_width,off_height;
    QString viewid;
    QRect m_rect;
    bool m_isfocus;
    bool isroot;
public:

   View();
   virtual void paint(QPaintEvent * event,QWidget * widget);

public:


    virtual void setSize(int p_width,int p_height);
    virtual void setPos(int x,int y);


     int max(int a,int b);
     int min(int a,int b);


    virtual bool isLine();
    virtual bool isLineTo(View *v);
    virtual bool isRoot();
    void setRoot(bool is);

     virtual bool isPointIn(const QPoint &p);
     QRect *getRect();

     void setFocus(bool focus);

     virtual void save(QXmlStreamWriter &writer);
     virtual bool load(QXmlStreamReader &reader );

     virtual const char* getTypeName(){ return typeid(*this).name(); };


     virtual void line(View *from,View * to){};

     virtual void newProperties(QList<MProperty*> ps);


};



#endif // VIEW_H
