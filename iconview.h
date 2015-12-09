#ifndef ICONVIEW_H
#define ICONVIEW_H
#include "view.h"

class IconView :public View
{

 public:
    QPixmap * m_bitmap;
    QString m_iconpath;

 public:
    IconView();
    IconView(const QString & imagepath);
    ~IconView();

    void setImage(const QString & imagepath);

    virtual void paint(QPaintEvent * event,QWidget * widget);

    virtual void save(QXmlStreamWriter &writer);
    virtual bool load(QXmlStreamReader &reader );


};


#endif // ICONVIEW_H
