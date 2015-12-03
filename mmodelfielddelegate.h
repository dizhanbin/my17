#ifndef MMODELFIELDDELEGATE_H
#define MMODELFIELDDELEGATE_H

#include <QStyledItemDelegate>


class MModelFieldDelegate : public QStyledItemDelegate
{


    Q_OBJECT
public:
    explicit  MModelFieldDelegate(QObject *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

public:
    QString field_name;
    int field_type;
    QString field_value;
    QString field_descript;
signals:

public slots:
      void slots_datachanged_name();
      void slots_datachanged_value();
      void slots_datachanged_descript();
      void slots_datachanged(int i);

};

#endif // MMODELFIELDDELEGATE_H
