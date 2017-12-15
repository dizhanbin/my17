#ifndef FORMVIEW_H
#define FORMVIEW_H

#include "view.h"


class FormView : public View
{

private:
   QPixmap * m_bitmap;

public:
    FormView();

    void paint(QPainter & painter,const QPalette & pal);

    virtual const QString & getDescript();
    MForm * form;


    virtual void setPos(int x,int y);
    void initFormData();

    virtual QList<MProperty*> & getProperties(){
        return form->properties;
    }

    virtual void setData(void * data){


    };
    virtual void* getData(){ return form; };
    virtual const QString & getTopDescript(){

        return getDescript();
    }

};

#endif // FORMVIEW_H
