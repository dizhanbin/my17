#ifndef DOCURLEDITOR_H
#define DOCURLEDITOR_H

#include <QWidget>
#include "messagecenter.h"
#include "murldelegate.h"
#include <QTableWidgetItem>

namespace Ui {
class DocUrlEditor;
}

class DocUrlEditor : public QWidget,public IExec
{
    Q_OBJECT

public:
    explicit DocUrlEditor(QWidget *parent = 0);
    ~DocUrlEditor();


    virtual my17::TodoResult  todo(my17::Event event,void * arg);
    virtual void setData(void * d);
    void setFieldData(int row,MUrlDelegate * urldata);

private:
    Ui::DocUrlEditor *ui;

public slots:
    void slot_onTableItemSelected(QTableWidgetItem * item);
};

#endif // DOCURLEDITOR_H
