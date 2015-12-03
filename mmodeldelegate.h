#ifndef MMODELDELEGATE_H
#define MMODELDELEGATE_H

#include <QStyledItemDelegate>
#include "mmodelfielddelegate.h"



class MModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MModelDelegate(QObject *parent = 0);



    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;


public:
    QString name;

    QList<MModelFieldDelegate*> fields;

signals:

public slots:
      void slots_datachanged();
};

#endif // MMODELDELEGATE_H
