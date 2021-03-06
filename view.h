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
    bool hasGlobalVar;


    QList<MProperty*> properties;

    virtual QList<MProperty*> & getProperties(){
        return properties;
    }

    virtual MProperty * getProperty(const QString & name);

    virtual void setData(void * data){};
    virtual void* getData(){ return NULL; };
    virtual void updateHasGlobalVar();

public:

   View();
   virtual void paint(QPaintEvent * event,QWidget * widget);
   virtual void paint(QPainter & painter,const QPalette & pal);

   virtual ~View();
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
     virtual void saveData(QXmlStreamWriter &writer,const QString & tag);


     virtual void createCodes(QXmlStreamWriter &writer);
     virtual void createProprityCodes(QXmlStreamWriter &writer,const QString & tag);


     virtual bool load(QXmlStreamReader &reader );
     virtual bool loadData(QXmlStreamReader &reader );

     virtual const char* getTypeName(){ return typeid(*this).name(); };


     virtual void line(View *from,View * to){};

     virtual void newProperties(QList<MProperty*> ps);

     virtual const QString & getDescript();
     virtual const QString & getTopDescript();//注释

     virtual  QString getXmlTag();
     virtual  QString getCodeTag();


     virtual  const QString&  getElementid(){ return "000"; };


};



#endif // VIEW_H
