#include "docformeditor.h"
#include "ui_docformeditor.h"

DocFormEditor::DocFormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocFormEditor)
{
    ui->setupUi(this);
}

DocFormEditor::~DocFormEditor()
{
    delete ui;
}
