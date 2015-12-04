#ifndef ICONVIEW_H
#define ICONVIEW_H
#include "view.h"

class IconView :public View
{

 public:
    QPixmap * m_bitmap;

 public:
    IconView(const QString & imagepath);
    ~IconView();

    virtual void paint(QPaintEvent * event,QWidget * widget);

};


#endif // ICONVIEW_H
