#include "doccommoneditor.h"
#include "ui_doccommoneditor.h"

DocCommonEditor::DocCommonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocCommonEditor)
{
    ui->setupUi(this);
}

DocCommonEditor::~DocCommonEditor()
{
    delete ui;
}
