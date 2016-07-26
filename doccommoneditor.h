#ifndef DOCCOMMONEDITOR_H
#define DOCCOMMONEDITOR_H

#include <QWidget>

namespace Ui {
class DocCommonEditor;
}

class DocCommonEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DocCommonEditor(QWidget *parent = 0);
    ~DocCommonEditor();

private:
    Ui::DocCommonEditor *ui;
};

#endif // DOCCOMMONEDITOR_H
