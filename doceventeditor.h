#ifndef DOCEVENTEDITOR_H
#define DOCEVENTEDITOR_H

#include <QWidget>
#include "messagecenter.h"
#include "meventdelegate.h"
#include <QTableWidgetItem>

namespace Ui {
class DocEventEditor;
}

class DocEventEditor : public QWidget,public IExec
{
    Q_OBJECT

public:
    explicit DocEventEditor(QWidget *parent = 0);
    ~DocEventEditor();

    virtual my17::TodoResult  todo(my17::Event event,void * arg);
    virtual void setData(void * d);
    void setFieldData(int row,MEventDelegate * event);
private:
    Ui::DocEventEditor *ui;

public slots:
    void slot_onTableItemSelected(QTableWidgetItem * item);

};

#endif // DOCEVENTEDITOR_H
