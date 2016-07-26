#ifndef DOCFORMEDITOR_H
#define DOCFORMEDITOR_H

#include <QWidget>

namespace Ui {
class DocFormEditor;
}

class DocFormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DocFormEditor(QWidget *parent = 0);
    ~DocFormEditor();

private:
    Ui::DocFormEditor *ui;
};

#endif // DOCFORMEDITOR_H
