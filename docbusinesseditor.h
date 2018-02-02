#ifndef DOCBUSINESSEDITOR_H
#define DOCBUSINESSEDITOR_H

#include <QWidget>
#include "viewdoc.h"
#include "messagecenter.h"

namespace Ui {
class DocBusinessEditor;
}

class DocBusinessEditor : public QWidget,public IExec
{
    Q_OBJECT

public:
    explicit DocBusinessEditor(QWidget *parent = 0);
    ~DocBusinessEditor();

    virtual my17::TodoResult  todo(my17::Event event,void * arg);
    virtual void setData(void *d);

     virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::DocBusinessEditor *ui;
    ViewDoc * mViewDoc;

protected:
    virtual void resizeEvent(QResizeEvent * qre);
};

#endif // DOCBUSINESSEDITOR_H
