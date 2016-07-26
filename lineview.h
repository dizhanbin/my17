#ifndef LINEVIEW_H
#define LINEVIEW_H

#include "view.h"

class LineView : public View
{

private:
    View * from;
    View * to;




    QPoint cursor;

    QList<QRect> path;

public:

    QString fromid;
    QString toid;


    LineView();

    void setFrom(View *fv);
    void setTo(View * tv);

    void setTo(int x,int y);
    virtual void paint(QPaintEvent * event,QWidget * widget);
    virtual void paint(QPainter & painter,const QPalette & pal);

    void drawArrow(QPainter & painter,float x1,float y1,float x2,float y2);

    void drawLine(QPainter & painter,int x0,int y0,int x1,int y1);


    virtual bool isPointIn(const QPoint &p);

    virtual bool isLine();
     virtual bool isLineTo(View *v);


     virtual void createCodes(QXmlStreamWriter &writer);
    virtual void save(QXmlStreamWriter &writer);


    virtual bool load(QXmlStreamReader &reader );


     virtual void line(View *from,View * to);

    virtual const QString & getXmlTag();

    void setDefProperty();
    virtual const QString &  getDescript();


    virtual const QString & getCodeTag();

};


#endif // LINEVIEW_H
