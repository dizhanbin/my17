#include "mpropertydelegate.h"
#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include <QComboBox>
#include "messagecenter.h"

MPropertyDelegate::MPropertyDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{


}


 void MPropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {

     if(properties && properties->count() <= index.row()  )
         return;

     if( index.column() == 0 )
      {
         QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
         painter->drawText(option.rect,properties->at(index.row())->p_title, o);
     }
     else
     {



         MProperty * mp = properties->at(index.row());
         QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);

         if( mp->p_type == 1 )
         {


             if( mp->p_args ==  "$model" )
             {
                 MModelDelegate * mmd = DP->getModelById(mp->p_value);
                 if( mmd )
                     painter->drawText(option.rect,mmd->name, o);

             }
             else if( mp->p_args ==  "$event" )
             {

                MEventDelegate * med = DP->getEventById(mp->p_value);


                if( med )
                {
                   NLog::i("paint event:%s  v:%s",med->event_name.toStdString().c_str(),mp->p_value.toStdString().c_str());
                   painter->drawText(option.rect,med->event_name, o);

                }

             }
             else if( mp->p_args == "$url" )
             {
                 MUrlDelegate * mud = DP->getUrlById(mp->p_value);
                 if( mud )
                      painter->drawText(option.rect,mud->url_name, o);

             }
             else if( mp->p_args == "$boolean" )
             {
                 painter->drawText(option.rect,mp->p_value, o);
             }
             else if( mp->p_args == "$formtype" )
             {

                painter->drawText(option.rect,mp->p_value, o);

             }

         }
         else
              painter->drawText(option.rect,mp->p_value, o);

     }






 }
QWidget * MPropertyDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{

    if( index.column() == 0 ) return NULL;

    MProperty * mp = properties->at(index.row());


    switch( mp->p_type  )
    {
        case 0:
    {
        QLineEdit *m_pTxt = new QLineEdit(parent);
        connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_text()) );

        return m_pTxt;


    }
        case 1:
    {

        QComboBox *comBox = new QComboBox(parent);



        if( mp->p_args.startsWith("$") )
        {
            if( mp->p_args == "$event" )
            {
                for(int i=0;i<DP->events.count();i++)
                {
                     comBox->addItem(  DP->events.at(i)->event_name +">"+ DP->events.at(i)->event_descript);
                }

            }
            else if( mp->p_args == "$model" )
            {

                for(int i=0;i<DP->models.count();i++)
                {

                    comBox->addItem( DP->models.at(i)->name );

                }

            }
            else if( mp->p_args == "$url" )
            {

                for(int i=0;i<DP->urls.count();i++)
                {

                    comBox->addItem( DP->urls.at(i)->url_name );

                }

            }
            else if( mp->p_args == "$boolean" )
            {


                comBox->addItem( "true" );
                comBox->addItem( "false" );
            }
            else if( mp->p_args == "$formtype" )
            {

                comBox->addItem("Empty");
                comBox->addItem("RecyclerView");
                comBox->addItem("Settings");

            }

        }


        connect(comBox,SIGNAL(currentIndexChanged(int )),this,SLOT(slots_datachanged_index(int)) );
        return comBox;

    }


    }
    return NULL;



}

 void MPropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {


     MProperty * mp = properties->at(index.row());
     switch( mp->p_type )
     {
        case 0:
        {
         QLineEdit * text = (QLineEdit*)editor;
         text->setProperty( "row",index.row() );

         if( text->text().length() == 0 )
             text->setText( mp->p_value );
        }
         break;
        case 1:
        {
             QComboBox *comBox = (QComboBox*)editor;
             comBox->setProperty("row",index.row());
             if( comBox->currentIndex() == 0 )
             {
                 if( mp->p_args == "$model" )
                 {
                     int index = DP->getModelIndexById( mp->p_value );
                     if( index >-1 )
                      comBox->setCurrentIndex(index);
                 }
                 else if( mp->p_args ==  "$event" )
                 {

                     int index = DP->getEventIndexById( mp->p_value );
                     if(index > -1 )
                      comBox->setCurrentIndex(index);

                 }
                 else if( mp->p_args ==  "$url" )
                 {

                     int index = DP->getUrlIndexById( mp->p_value );
                     if(index > -1 )
                      comBox->setCurrentIndex(index);

                 }
                else if( mp->p_args ==  "$boolean" )
                 {
                     int index = ( mp->p_value == "true" )? 0 : 1;
                     comBox->setCurrentIndex(index);

                 }
                 else if( mp->p_args == "$formtype" ){

                     int index = -1;

                     if( mp->p_value == "Empty")
                         index = 0;
                     else if( mp->p_value == "RecyclerView" )
                         index = 1;
                     else if( mp->p_value == "Settings" )
                         index = 2;
                     comBox->setCurrentIndex(index);


                 }


             }
        }
          break;



     }






 }


 void MPropertyDelegate::slots_datachanged_text()
 {


      QLineEdit * text = (QLineEdit*)sender();
      int index = text->property("row").value<int>();
      MProperty * mp = properties->at(index);
      mp->p_value = text->text();
      QString var;
      if( DP->getGlobalVar(mp->p_value,&var)>-1 ){
         DP->addVarString(mp->p_value,DP->current_business,false);
      }
      view_focus->updateHasGlobalVar();

     // NLog::i("data changed...index:%d",index);


 }
 void MPropertyDelegate::slots_datachanged_index(int i)
 {
     QComboBox *comBox = (QComboBox*)sender();
      int index = comBox->property("row").value<int>();
      //NLog::i("data combox changed...index:%d  p-index:%d",i,index);


     MProperty * mp = properties->at(index);
     if( mp->p_args == "$model" )
     {
         mp->p_value =  DP->models.at(i)->id;
     }
     else if(  mp->p_args == "$event"  )
     {
         mp->p_value = DP->events.at(i)->event_id;

          NLog::i("data combox changed value:%s title:%s", mp->p_value.toStdString().c_str(),  DP->events.at(i)->event_name.toStdString().c_str());

     }
     else if(  mp->p_args == "$url"  )
     {
         mp->p_value = DP->urls.at(i)->url_id;

     }
     else if(  mp->p_args == "$boolean"  )
     {
         mp->p_value = i==0? "true":"false";
     }
     else if( mp->p_args == "$formtype" )
     {


         switch (i) {
             case 0:
                 mp->p_value = "Empty";
                 break;
             case 1:
                 mp->p_value = "RecyclerView";
                 break;
             case 2:
                 mp->p_value = "Settings";
                 break;
             default:
                 mp->p_value = "Empty";
                 break;
         }


     }

 }
