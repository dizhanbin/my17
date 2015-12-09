#include "mpropertydelegate.h"


MPropertyDelegate::MPropertyDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{


}


 void MPropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {






 }
QWidget * MPropertyDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{

    return NULL;

}

 void MPropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {



 }
