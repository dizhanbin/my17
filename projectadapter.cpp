#include "projectadapter.h"
#include "my17.h"

ProjectAdapter::ProjectAdapter()
{
}



 const QString  ProjectAdapter::getHeder(int col)
 {

     switch( col )
     {

         case 0 : return "变量名";
         case 1 : return "值";
         case 2 : return "描述";


     }
     return "";
 }
 const QString ProjectAdapter::getValue(int row,int col)
 {
    MData * data = DP->projectinfos.at(row);

    switch(col)
    {

        case 0 : return data->key;
    case 1 : return data->value;
    case 2: return data->descript;

    }
    return "";
 }
 int ProjectAdapter::getRowCount()
 {

     return DP->projectinfos.count();
 }
 int ProjectAdapter::getColCount()
 {


     return 3;

 }
 void ProjectAdapter::onValueChanged(int row,int col,const QString & value)
 {

     MData * data = DP->projectinfos.at(row);

     switch( col )
     {

        case 0:
            data->key = value;
            break;
        case 1:
         data->value = value;
         break;
     case 2:
         data->descript = value;
         break;


     }

 }
 bool ProjectAdapter::isEditable(int row,int col)
 {
     return col!=0;

 }
