#include "commoneditdelegate.h"
#include <QLineEdit>
#include <QtGui>
#include <QComboBox>
#include "messagecenter.h"

CommonEditDelegate::CommonEditDelegate(QObject * parent):
    QStyledItemDelegate(parent)
{
}


 void CommonEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


     QTextOption o(Qt::AlignHCenter | Qt::AlignVCenter);




     if( index.column() == 0 )
     {
          const QString  str =  adapter->getEditTitle(index.row());
          painter->drawText(option.rect, str,  o);
     }
     else
     {
         const QString  str =  adapter->getEditValue(index.row(),1);
         painter->drawText(option.rect, str,  o);

     }



}
QWidget * CommonEditDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{


    QLineEdit *m_pTxt = new QLineEdit(parent);


    QVariant q(index.row());

    m_pTxt->setProperty("index",q);

    connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged()) );
    return m_pTxt;

}

  void CommonEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QLineEdit *m_pTxt = ( QLineEdit *)editor;
    if( m_pTxt->text().length() == 0 )
        m_pTxt->setText( adapter->getEditValue(index.row(),1) );

}

  void CommonEditDelegate::slots_datachanged()
  {

        QLineEdit *m_pTxt = (QLineEdit *)sender();
        QVariant q = m_pTxt->property("index");

        NLog::i("text changed index:%d text:%s",q.toInt(),m_pTxt->text().toStdString().c_str() );

        adapter->setEditorValue(m_pTxt->text(),q.toInt(),1);


        MC->sendMessage(my17::event_property_changed,&q);


  }
