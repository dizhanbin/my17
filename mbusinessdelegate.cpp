#include "mbusinessdelegate.h"
#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include "messagecenter.h"


MBusinessDelegate::MBusinessDelegate(QObject *parent ):QStyledItemDelegate(parent)
{
}


void MBusinessDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    switch( index.column() ){

        case 0:
        {
            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, "名称", o);
        }
        break;
        case 1:
        {

            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, name, o);

        }
        break;


    }


}

QWidget *MBusinessDelegate::createEditor(QWidget *parent,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{


   NLog::i("MModel delegate  createEditor index:%d,%d",index.row(),index.column());

    switch( index.column() )
    {
        case 1:
         QLineEdit *m_pTxt = new QLineEdit(parent);
         connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged()));
         return m_pTxt;

    }
    return NULL;



}

void MBusinessDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{



   QLineEdit * text = (QLineEdit*)editor;


   switch( index.column() )
   {

        case 1:
        {
            if( text->text().length() == 0 )
               text->setText(this->name );
        }
            break;
   }

}


void MBusinessDelegate::slots_datachanged()
{

      NLog::i("MModel delegate  slots_datachanged");

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);


      QLineEdit * text = qobject_cast<QLineEdit *>( sender() );
      this->name =  text->text();

      MessageCenter::getInstence()->sendMessage(my17::event_req_business_data_changed,this);


}
