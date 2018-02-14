#ifndef FORMJSDO_H
#define FORMJSDO_H

#include "ftmp.h"

class JS_FormLinkCase : public JSDo{

public:
    virtual QString create_form_codes(MForm * from,const QString & arg ="" );


};


class JS_LayoutLink : public JSDo{

public:
   virtual QString create_form_codes(MForm * from,const QString & arg ="" );


};

#endif // FORMJSDO_H
