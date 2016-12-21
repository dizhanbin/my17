#ifndef MEVENTDELEGATE_H
#define MEVENTDELEGATE_H

#include <QStyledItemDelegate>



class MEventDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MEventDelegate(QObject * parent=0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

public:
    QString event_id;
    QString event_name;
    int event_type;
    QString event_descript;

    bool operator >(const MEventDelegate * arg){
        return event_name.compare(arg->event_name)>0;
    }

    bool operator <(const MEventDelegate * arg){
        return event_name.compare(arg->event_name)<0;
    }
    bool operator ==(const MEventDelegate * arg){
        return event_name.compare(arg->event_name)==0;
    }

    bool operator >=(const MEventDelegate * arg){
        return event_name.compare(arg->event_name)>=0;
    }
    bool operator <=(const MEventDelegate * arg){
        return event_name.compare(arg->event_name)<=0;
    }


signals:

public slots:
      void slots_datachanged_name();
      void slots_datachanged_type(int);
      void slots_datachanged_descript();
//      void slots_datachanged(int i);


};

#endif // MEVENTDELEGATE_H
