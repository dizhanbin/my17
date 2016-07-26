#include "mproperty.h"

MProperty::MProperty()
{
}


MProperty * MProperty::copy()
{


    MProperty * p = new MProperty();
    p->p_args = this->p_args;
    p->p_name = this->p_name;
    p->p_title = this->p_title;
    p->p_type = this->p_type;
    p->p_value = this->p_value;

    return p;

}

MProperty & MProperty::operator=(const MProperty & p)
{

    this->p_args = p.p_args;
    this->p_name = p.p_name;
    this->p_title = p.p_title;
    this->p_type = p.p_type;
    this->p_value = p.p_value;
    return *this;
}
