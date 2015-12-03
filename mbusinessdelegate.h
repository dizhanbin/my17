#ifndef MBUSINESSDELEGATE_H
#define MBUSINESSDELEGATE_H

#include <QStyledItemDelegate>

class MBusinessDelegate : public QStyledItemDelegate
{

    Q_OBJECT
public:
    MBusinessDelegate(QObject *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
     QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;


public:
    QString name;

signals:

public slots:
      void slots_datachanged();

};

#endif // MBUSINESSDELEGATE_H
