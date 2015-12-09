#ifndef MURLDELEGATE_H
#define MURLDELEGATE_H

#include <QStyledItemDelegate>

class MUrlDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit  MUrlDelegate(QObject *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
public:
    QString url_name;
    QString url_address;
    QString url_descript;

public slots:
      void slots_datachanged_name();
      void slots_datachanged_address();
      void slots_datachanged_descript();


};

#endif // MURLDELEGATE_H
