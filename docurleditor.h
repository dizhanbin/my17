#ifndef DOCURLEDITOR_H
#define DOCURLEDITOR_H

#include <QWidget>

namespace Ui {
class DocUrlEditor;
}

class DocUrlEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DocUrlEditor(QWidget *parent = 0);
    ~DocUrlEditor();

private:
    Ui::DocUrlEditor *ui;
};

#endif // DOCURLEDITOR_H
