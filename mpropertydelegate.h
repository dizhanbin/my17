#ifndef MPROPERTYDELEGATE_H
#define MPROPERTYDELEGATE_H

#include <QStyledItemDelegate>
#include "mproperty.h"

class MPropertyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit  MPropertyDelegate(QObject *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

public:
    QList<MProperty*> * properties;


public slots:

      void slots_datachanged_text();
      void slots_datachanged_index(int i);



};

#endif // MPROPERTYDELEGATE_H
