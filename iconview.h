#ifndef ICONVIEW_H
#define ICONVIEW_H
#include "view.h"

class IconView :public View
{

 public:
    QPixmap * m_bitmap;
    QString  m_element_id;


 public:
    IconView();
    ~IconView();

    virtual void paint(QPaintEvent * event,QWidget * widget);


     virtual void createCodes(QXmlStreamWriter &writer);
    virtual void save(QXmlStreamWriter &writer);
    virtual bool load(QXmlStreamReader &reader );

    virtual const QString & getTopDescript();//注释

    virtual  QString  getCodeTag();

    virtual const QString & getElementid(){ return m_element_id; };

};


#endif // ICONVIEW_H
