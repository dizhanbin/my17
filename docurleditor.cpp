#include "docurleditor.h"
#include "ui_docurleditor.h"

DocUrlEditor::DocUrlEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocUrlEditor)
{
    ui->setupUi(this);
}

DocUrlEditor::~DocUrlEditor()
{
    delete ui;
}
