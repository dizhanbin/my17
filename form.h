#ifndef FORM_H
#define FORM_H
#include "my17.h"
class Form
{
public:
    Form();

    my17::TodoResult onMessage(my17::Event event,void * arg);

};


#endif // FORM_H
