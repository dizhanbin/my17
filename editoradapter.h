#ifndef EDITORADAPTER_H
#define EDITORADAPTER_H

#include <QStyledItemDelegate>
#include "nlog.h"

class EditorAdapter
{
public:




    virtual  int getEditRowCount() {

        NLog::i("getEditRowCount in super");
        return 0;

    };
    virtual const QString  getEditDescript() =0;
    virtual const QString  getEditTitle(int row)=0;
    virtual const QString  getEditValue(int row,int col)=0;
    virtual QWidget * getEditor(QWidget *parent,int row,int col)=0 ;
    virtual void setEditorValue(const QString & text,int row,int col)=0;



};

#endif // EDITORADAPTER_H
