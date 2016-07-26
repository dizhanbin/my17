#ifndef FORMLINEVIEW_H
#define FORMLINEVIEW_H
#include "lineview.h"

class FormLineView : public LineView
{
public:
    FormLineView();

    MLine * mline;

    virtual QList<MProperty*> & getProperties(){
        return mline->properties;
    }

     virtual const  QString &  getDescript()
    {

        if(  mline->properties.count( ) > 0 ){
          return  mline->properties.at(0)->p_value;
        }
        else{


            MProperty * mp = new MProperty();

            mp->p_name = "value";
            mp->p_title = "条件";
            mp->p_type = 0;
            mp->p_value = "";
            mline->properties.push_back(mp);
            return mp->p_value;

        }


    }

};

#endif // FORMLINEVIEW_H
