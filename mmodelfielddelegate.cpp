#include "mmodelfielddelegate.h"
#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include <QComboBox>
#include "messagecenter.h"




MModelFieldDelegate::MModelFieldDelegate(QObject *parent):
    QStyledItemDelegate(parent),field_type(0)
{


}





void MModelFieldDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if( index.column() == 0 )
     {
        QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
        switch( index.row() )
        {
            case 0:
            painter->drawText(option.rect, RP->model_title_index(0), o);
            break;
            case 1:
            painter->drawText(option.rect, RP->model_title_index(1), o);
            break;
            case 2:
            painter->drawText(option.rect, RP->model_title_index(2), o);
            break;
            case 3:
            painter->drawText(option.rect, RP->model_title_index(3), o);
            break;


        }
    }
    else
    {

        QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
        switch( index.row() )
        {

            case 0:
            painter->drawText(option.rect,field_name, o);
            break;
            case 1:
            painter->drawText(option.rect, RP->model_field_type_index(field_type), o);
            break;
            case 2:
            painter->drawText(option.rect, field_value, o);
            break;
            case 3:
            painter->drawText(option.rect, field_descript, o);
            break;

        }
    }


}

QWidget *MModelFieldDelegate::createEditor(QWidget *parent,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{


   NLog::i("MModel delegate  createEditor index:%d,%d",index.row(),index.column());

   if( index.column() == 1 )
    switch( index.row() )
    {
        case 0:
    {
         QLineEdit *m_pTxt = new QLineEdit(parent);
         connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_name()) );

         return m_pTxt;
    }
        case 2:
    {
         QLineEdit *m_pTxt = new QLineEdit(parent);
         connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_value()) );

         return m_pTxt;
    }
        case 3:
        {
             QLineEdit *m_pTxt = new QLineEdit(parent);
             connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_descript()) );

             return m_pTxt;
        }
        case 1:
        {
            QComboBox *comBox = new QComboBox(parent);

            comBox->addItem( RP->model_field_type_index(0) );
            comBox->addItem( RP->model_field_type_index(1) );
            comBox->addItem( RP->model_field_type_index(2) );

            //comBox->setCurrentIndex( field_type );

            connect(comBox,SIGNAL(currentIndexChanged(int )),this,SLOT(slots_datachanged(int)) );

            return comBox;
         }

    }
    return NULL;



}

void MModelFieldDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{


    switch( index.row() )
    {
        case 0:
    {
        QLineEdit * text = (QLineEdit*)editor;
        if( text->text().length() == 0 )
            text->setText( field_name );


    }
        case 2:
    {
        QLineEdit * text = (QLineEdit*)editor;
         if( text->text().length() == 0 )
        text->setText( field_value );
    }
        case 3:
    {
        QLineEdit * text = (QLineEdit*)editor;
         if( text->text().length() == 0 )
        text->setText( field_descript );
    }
        break;
        case 1:
    {
        QComboBox *comBox = (QComboBox*)editor;
         if( comBox->currentIndex() == 0 )
            comBox->setCurrentIndex(field_type);
    }
        break;
    }



}


void MModelFieldDelegate::slots_datachanged(int i)
{

    field_type = i;

   // NLog::i("MModel delegate  slots_datachanged index:%d",i);

    MC->sendMessage(my17::event_req_model_field_changed,this );

}



void MModelFieldDelegate::slots_datachanged_name()
{

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);
      this->field_name = editor->text();
       MC->sendMessage(my17::event_req_model_field_changed,this);

}

void MModelFieldDelegate::slots_datachanged_value()
{

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);
      this->field_value = editor->text();

       MC->sendMessage(my17::event_req_model_field_changed,this);
}
void MModelFieldDelegate::slots_datachanged_descript()
{

      QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
      emit commitData(editor);
      emit closeEditor(editor);
      this->field_descript = editor->text();

       MC->sendMessage(my17::event_req_model_field_changed,this);
}
