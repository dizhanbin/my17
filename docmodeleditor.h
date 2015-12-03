#ifndef DOCMODELEDITOR_H
#define DOCMODELEDITOR_H

#include <QWidget>
#include <QTableWidgetItem>
#include "messagecenter.h"

namespace Ui {
class DocModelEditor;
}

class DocModelEditor : public QWidget,public IExec
{
    Q_OBJECT

public:
    explicit DocModelEditor(QWidget *parent = 0);
    ~DocModelEditor();
    virtual my17::TodoResult  todo(my17::Event event,void * arg);
    void setFieldData(int row,MModelFieldDelegate * field);
private:
    Ui::DocModelEditor *ui;

public slots:
    void slot_onTableItemSelected(QTableWidgetItem * item);

};

#endif // DOCMODELEDITOR_H
