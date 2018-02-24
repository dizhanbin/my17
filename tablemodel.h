#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QString>

class TableAdapter
{
public:
    TableAdapter();

    virtual const QString  getHeder(int col)=0;
    virtual const QString  getValue(int row,int col)=0;
    virtual int getRowCount()=0;
    virtual int getColCount()=0;
    virtual void onValueChanged(int row,int col,const QString & value)=0;
    virtual bool isEditable(int row,int col)=0;
    virtual bool deleteRow(int row)=0;
    virtual void addRow()=0;



};

#endif // TABLEMODEL_H
