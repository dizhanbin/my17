#ifndef DOCFORMEDITOR_H
#define DOCFORMEDITOR_H

#include <QWidget>
#include "viewforms.h"
#include "messagecenter.h"

namespace Ui {
class DocFormEditor;
}

class DocFormEditor : public QWidget,public IExec
{
    Q_OBJECT

public:
    explicit DocFormEditor(QWidget *parent = 0);
    ~DocFormEditor();

    virtual my17::TodoResult  todo(my17::Event event,void * arg);

    ViewForms * mViewForm;
private:
    Ui::DocFormEditor *ui;

protected:
    virtual void resizeEvent(QResizeEvent * qre);

};

#endif // DOCFORMEDITOR_H
