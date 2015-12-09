#include "murldelegate.h"

#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include "messagecenter.h"


MUrlDelegate::MUrlDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{


}

 void MUrlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {

     if( index.column() == 0 )
      {
         QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
         switch( index.row() )
         {
             case 0:
             painter->drawText(option.rect, RP->url_title_index(0), o);
             break;
             case 1:
             painter->drawText(option.rect, RP->url_title_index(1), o);
             break;
             case 2:
             painter->drawText(option.rect, RP->url_title_index(2), o);
             break;

         }
     }
     else
     {

         QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
         switch( index.row() )
         {

             case 0:
             painter->drawText(option.rect,url_name, o);
             break;
             case 1:
             painter->drawText(option.rect,url_address, o);
             break;
             case 2:
             painter->drawText(option.rect,url_descript, o);
             break;

         }
     }

 }
QWidget *MUrlDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{

    if( index.column() == 1 )
     switch( index.row() )
     {
         case 0:
     {
          QLineEdit *m_pTxt = new QLineEdit(parent);
          connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_name()) );

          return m_pTxt;
     }
         case 1:
     {
          QLineEdit *m_pTxt = new QLineEdit(parent);
          connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_address()) );

          return m_pTxt;
     }
         case 2:
         {
              QLineEdit *m_pTxt = new QLineEdit(parent);
              connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_descript()) );

              return m_pTxt;
         }


     }
     return NULL;

}

 void MUrlDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {

     switch( index.row() )
     {
         case 0:
         {
             QLineEdit * text = (QLineEdit*)editor;
             if( text->text().length() == 0 )
                 text->setText( url_name );


         }
         case 1:
         {
             QLineEdit * text = (QLineEdit*)editor;
              if( text->text().length() == 0 )
             text->setText( url_address );
         }
         case 2:
         {
             QLineEdit * text = (QLineEdit*)editor;
              if( text->text().length() == 0 )
             text->setText( url_descript );
         }
         break;

     }


 }


 void MUrlDelegate::slots_datachanged_name()
 {


     QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
     emit commitData(editor);
     emit closeEditor(editor);
     this->url_name = editor->text();
      MC->sendMessage(my17::event_req_url_item_data_changed,this);

 }
 void MUrlDelegate::slots_datachanged_address()
 {

     QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
     emit commitData(editor);
     emit closeEditor(editor);
     this->url_address = editor->text();
      MC->sendMessage(my17::event_req_url_item_data_changed,this);


 }
 void MUrlDelegate::slots_datachanged_descript()
 {

     QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
     emit commitData(editor);
     emit closeEditor(editor);
     this->url_descript = editor->text();
      MC->sendMessage(my17::event_req_url_item_data_changed,this);

 }
