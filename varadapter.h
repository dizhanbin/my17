#ifndef VARADAPTER_H
#define VARADAPTER_H

#include "tablemodel.h"

class VarAdapter : public TableAdapter
{
public:
    VarAdapter();

    virtual const QString  getHeder(int col);
    virtual const QString  getValue(int row,int col);
    virtual int getRowCount();
    virtual int getColCount();
    virtual void onValueChanged(int row,int col,const QString & value);
    virtual bool isEditable(int row,int col);
};

#endif // VARADAPTER_H
