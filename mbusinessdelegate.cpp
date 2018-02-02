#include "mbusinessdelegate.h"
#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include "messagecenter.h"
#include "viewgroup.h"
#include <QComboBox>

MBusinessDelegate::MBusinessDelegate(QObject *parent ):QStyledItemDelegate(parent)
{

    viewgroup = new ViewGroup();
    type = 1;

}

MBusinessDelegate:: ~MBusinessDelegate()
{

    delete viewgroup;


}


void MBusinessDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if( index.column() == 0 )
    switch( index.row() ){

        case 0:
        {
            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, "名称", o);
        }
        break;
        case 1:
        {

            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, "类型", o);

        }
        break;
        case 2:
        {
            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, "流程保存名", o);
        }
        break;
        case 3:
        {
            QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
            painter->drawText(option.rect, "流程描述", o);

        }
        break;




    }
    else if( index.column() ==  1)
    switch( index.row() ){


            case 0:
            {
                QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
                painter->drawText(option.rect, name, o);
            }
            break;
            case 2:
            {
                QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
                painter->drawText(option.rect, alia, o);
            }
            break;
            case 1:
            {

                QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
                painter->drawText(option.rect,RP->business_type_index(type), o);

            }
            break;
            case 3:
            {
                QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
                painter->drawText(option.rect, descript, o);
            }
            break;

    }


}

QWidget *MBusinessDelegate::createEditor(QWidget *parent,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{


   NLog::i("MModel delegate  createEditor index:%d,%d",index.row(),index.column());

   if( index.column() == 1 )
    switch( index.row() )
    {
        case 2:
        {
             QLineEdit *m_pTxt = new QLineEdit(parent);
             connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_alia()) );

             return m_pTxt;
        }


        case 0:
        {
             QLineEdit *m_pTxt = new QLineEdit(parent);
             connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged()) );

             return m_pTxt;
        }
        case 1:
        {
            QComboBox *comBox = new QComboBox(parent);

            comBox->addItem( RP->business_type_index(0) );
            comBox->addItem( RP->business_type_index(1) );

            connect(comBox,SIGNAL(currentIndexChanged(int )),this,SLOT(slots_datachanged_type(int)) );

            return comBox;
         }
        case 3:
        {
             QLineEdit *m_pTxt = new QLineEdit(parent);
             connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_descript()) );

             return m_pTxt;
        }

    }
    return NULL;




}

void MBusinessDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{






   if( index.column() == 1)
   switch( index.row() )
   {

        case 2:
       {

           QLineEdit * text = (QLineEdit*)editor;
           if( text->text().length() == 0 )
              text->setText(this->alia );

       }
        break;
        case 0:
        {

            QLineEdit * text = (QLineEdit*)editor;
            if( text->text().length() == 0 )
               text->setText(this->name );
        }
            break;
        case 1:
       {

         QComboBox *comBox = (QComboBox*)editor;
         if( comBox->currentIndex() == 0 )
             comBox->setCurrentIndex(type);

       }
           break;
       case 3:
       {

           QLineEdit * text = (QLineEdit*)editor;
           if( text->text().length() == 0 )
              text->setText(this->descript );
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
void MBusinessDelegate::slots_datachanged_descript()
{

      NLog::i("MModel delegate  slots_datachanged");

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);


      QLineEdit * text = qobject_cast<QLineEdit *>( sender() );
      this->descript =  text->text();

      MessageCenter::getInstence()->sendMessage(my17::event_req_business_data_changed,this);


}


void MBusinessDelegate::slots_datachanged_alia()
{

      NLog::i("MModel delegate  slots_datachanged");

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);


      QLineEdit * text = qobject_cast<QLineEdit *>( sender() );
      this->alia =  text->text();

      MessageCenter::getInstence()->sendMessage(my17::event_req_business_data_changed,this);


}

void MBusinessDelegate::slots_datachanged_type(int t)
{
    QComboBox * comb = (QComboBox*)sender();
    this->type = comb->currentIndex();
    MessageCenter::getInstence()->sendMessage(my17::event_req_business_data_changed,this);

}
