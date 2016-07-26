#ifndef DOCCOMMONEDITOR_H
#define DOCCOMMONEDITOR_H

#include <QWidget>
#include "messagecenter.h"
#include "tablemodel.h"
#include "editoradapter.h"

namespace Ui {
class DocCommonEditor;
}

class DocCommonEditor : public QWidget,public IExec,public EditorAdapter
{
    Q_OBJECT

public:
    explicit DocCommonEditor(QWidget *parent = 0);
    ~DocCommonEditor();

    virtual my17::TodoResult  todo(my17::Event event,void * arg);

    void setAdapter(TableAdapter * a);



    ////////// EditorAdapter

    virtual  int getEditRowCount() ;
    virtual const QString  getEditDescript() ;
    virtual const QString  getEditTitle(int row);
    virtual const QString  getEditValue(int row,int col);
    virtual QWidget * getEditor(QWidget *parent,int row,int col) ;
    virtual void setEditorValue(const QString & text,int row,int col);

    TableAdapter * adapter;

public slots :

    void slot_onCellSelected(int row,int col);



private:
    Ui::DocCommonEditor *ui;
    int row_selected;

};

#endif // DOCCOMMONEDITOR_H
