#include "meventdelegate.h"
#include "nlog.h"
#include <QLineEdit>
#include <QtGui>
#include <QComboBox>
#include "messagecenter.h"


MEventDelegate::MEventDelegate(QObject * parent):QStyledItemDelegate(parent),event_type(1)
{


}


void MEventDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if( index.column() == 0 )
     {
        QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
        switch( index.row() )
        {
            case 0:
            painter->drawText(option.rect, RP->event_title_index(0), o);
            break;
            case 1:
            painter->drawText(option.rect, RP->event_title_index(1), o);
            break;
            case 2:
            painter->drawText(option.rect, RP->event_title_index(2), o);
            break;


        }
    }
    else
    {

        QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);
        switch( index.row() )
        {

            case 0:
            painter->drawText(option.rect,event_name, o);
            break;
            case 1:
            painter->drawText(option.rect, RP->event_type_index(event_type), o);
            break;
            case 2:
            painter->drawText(option.rect, event_descript, o);
            break;


        }
    }


}

QWidget *MEventDelegate::createEditor(QWidget *parent,
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
         connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_descript()) );

         return m_pTxt;
    }

        case 1:
        {
            QComboBox *comBox = new QComboBox(parent);

            comBox->addItem( RP->event_type_index(0) );
            comBox->addItem( RP->event_type_index(1) );
            comBox->addItem( RP->event_type_index(2) );
            connect(comBox,SIGNAL(currentIndexChanged(int )),this,SLOT(slots_datachanged_type(int)) );

            return comBox;
         }

    }
    return NULL;



}

void MEventDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{


    switch( index.row() )
    {
        case 0:
    {
        QLineEdit * text = (QLineEdit*)editor;
        if( text->text().length() == 0 )
            text->setText( event_name );

    }
        case 2:
    {
        QLineEdit * text = (QLineEdit*)editor;
         if( text->text().length() == 0 )
        text->setText( event_descript );
    }
          break;
        case 1:
    {
        QComboBox *comBox = (QComboBox*)editor;
         if( comBox->currentIndex() == 0 )
            comBox->setCurrentIndex(event_type);
    }
        break;
    }



}


void MEventDelegate::slots_datachanged_name()
{
       QLineEdit * text = (QLineEdit*)sender();
    this->event_name = text->text();
    MC->sendMessage(my17::event_req_event_item_data_changed,this);

}
void MEventDelegate::slots_datachanged_type(int)
{
    QComboBox * comb = (QComboBox*)sender();

    this->event_type = comb->currentIndex();
    MC->sendMessage(my17::event_req_event_item_data_changed,this);

}
void MEventDelegate::slots_datachanged_descript()
{
    QLineEdit * text = (QLineEdit*)sender();
    this->event_descript = text->text();
    MC->sendMessage(my17::event_req_event_item_data_changed,this);

}
