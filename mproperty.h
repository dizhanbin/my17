#ifndef MPROPERTY_H
#define MPROPERTY_H
#include <QString>

class MProperty
{
public:

public:
    QString p_name;
    QString p_title;
    int p_type;//0 edit 1 combox
    QString p_args;//$model $url $event
    QString p_value;

    MProperty();

    MProperty * copy();
    MProperty &operator=(const MProperty &);

};

#endif // MPROPERTY_H
