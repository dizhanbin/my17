#ifndef PROJECTADAPTER_H
#define PROJECTADAPTER_H

#include "tablemodel.h"

class ProjectAdapter : public TableAdapter
{
public:
    ProjectAdapter();

    virtual const QString  getHeder(int col);
    virtual const QString  getValue(int row,int col);
    virtual int getRowCount();
    virtual int getColCount();
    virtual void onValueChanged(int row,int col,const QString & value);
    virtual bool isEditable(int row,int col);
    virtual bool deleteRow(int row);
    virtual void addRow();

};

#endif // PROJECTADAPTER_H
