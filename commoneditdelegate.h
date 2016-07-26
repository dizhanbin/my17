#ifndef COMMONEDITDELEGATE_H
#define COMMONEDITDELEGATE_H

#include <QStyledItemDelegate>
#include "editoradapter.h"


class CommonEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CommonEditDelegate(QObject * parent=0);

    EditorAdapter * adapter;

    void setAdapter(EditorAdapter * ada){

        adapter = ada;
    };



    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

     virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:

public slots:
    void slots_datachanged();



};

#endif // COMMONEDITDELEGATE_H
