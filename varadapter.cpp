#include "varadapter.h"

#include "my17.h"

VarAdapter::VarAdapter()
{

}


const QString  VarAdapter::getHeder(int col)
{

    switch( col )
    {

        case 0 : return "变量名";
        case 1 : return "描述";


    }
    return "";
}
const QString VarAdapter::getValue(int row,int col)
{


   switch(col)
   {

       case 0 : return DP->qlobal_vars.at(row)->key;
       case 1 : return DP->qlobal_vars.at(row)->descript;


   }
   return "";
}
int VarAdapter::getRowCount()
{

    return DP->qlobal_vars.size();
}
int VarAdapter::getColCount()
{


    return 2;

}
void VarAdapter::onValueChanged(int row,int col,const QString & value)
{

    if( col == 0 ) return;

    MData * data = DP->qlobal_vars.at(row);

    switch( col )
    {

       case 0:
           data->key = value;
       break;
       case 1:
           data->descript = value;
        break;


    }

}


bool VarAdapter::isEditable(int row,int col)
{

    return row==1&&col==1;
}

 bool VarAdapter::deleteRow(int row)
 {
     DP->qlobal_vars.takeAt(row);
     return true;

 }
 void VarAdapter::addRow()
 {

 }
