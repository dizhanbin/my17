#ifndef MBUSINESSDELEGATE_H
#define MBUSINESSDELEGATE_H


#include <QStyledItemDelegate>

class ViewGroup;

class MBusinessDelegate : public QStyledItemDelegate
{

    Q_OBJECT
public:
    MBusinessDelegate(QObject *parent = 0);
    ~MBusinessDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
     QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;


public:

    QString name;
    int type; //business_type_index

    ViewGroup * viewgroup;

signals:

public slots:
      void slots_datachanged();
      void slots_datachanged_type(int);

};

#endif // MBUSINESSDELEGATE_H
