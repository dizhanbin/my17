#include "docmodeleditor.h"
#include "ui_docmodeleditor.h"
#include "mmodeldelegate.h"
#include <QStandardItemModel>
#include <QComboBox>

DocModelEditor::DocModelEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocModelEditor)
{
    ui->setupUi(this);

    QStringList headers;

    headers.append(RP->model_title_index(0));
    headers.append(RP->model_title_index(1));
    headers.append(RP->model_title_index(2));
    headers.append(RP->model_title_index(3));

    //model->setHorizontalHeaderLabels(headers);

    //ui->mtable->setHorizontalHeaderLabels(headers);
    ui->mtable->setColumnCount(4);
    ui->mtable->setHorizontalHeaderLabels(headers);


    ui->mtable->horizontalHeader()->setStretchLastSection(true);
    //使行列头自适应宽度，所有列平均分来填充空白部分
    ui->mtable->horizontalHeader()->sectionResizeMode( QHeaderView::Stretch);


    ui->mtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置只能选择一行，不能选择多行
    ui->mtable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->mtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

   // ui->mtable->verticalHeader()->setResizeMode(QHeaderView::Strtch);

    ui->mtable->setAlternatingRowColors(1);
    QHeaderView *headerView =  ui->mtable->verticalHeader();
    headerView->setHidden(true);





    connect(ui->mtable,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(slot_onTableItemSelected(QTableWidgetItem *)) );



}


 void DocModelEditor::slot_onTableItemSelected(QTableWidgetItem * item)
 {

     MModelDelegate * model = static_cast<MModelDelegate *>(getData());



     MC->sendMessage(my17::event_req_model_field_selected,model->fields.at(item->row()));


     NLog::i("on row selected:");

 }
void DocModelEditor::setData(void * d)
 {
     IExec::setData(d);

     MModelDelegate * mmd =( MModelDelegate *) d;

     for(int i=0;i<mmd->fields.count();i++)
     {
         MModelFieldDelegate * field = mmd->fields.at(i);
        ui->mtable->insertRow(ui->mtable->rowCount());
        setFieldData(ui->mtable->rowCount()-1,field);
     }
 }


my17::TodoResult  DocModelEditor::todo(my17::Event event,void * arg)
{

    switch( event )
    {

        case my17::event_req_toolbar_add:
        {
            NLog::i("DocModelEditor event_req_toolbar_add");

            ui->mtable->insertRow(ui->mtable->rowCount());
            ui->mtable->selectRow(ui->mtable->rowCount()-1);

            MModelDelegate * model = static_cast<MModelDelegate *>(getData());


            MModelFieldDelegate * field = new MModelFieldDelegate();
            model->fields.push_back(field);


            setFieldData(ui->mtable->rowCount()-1,field);

            MC->sendMessage(my17::event_req_model_field_selected,field);


        }
        return my17::todo_done_only;

    case my17::event_req_model_field_changed:
    {
        MModelFieldDelegate * field = (MModelFieldDelegate*)arg;

        MModelDelegate * model = static_cast<MModelDelegate *>(getData());


        int index = model->fields.indexOf(field);


       setFieldData(index,field);

    }
        return my17::todo_done_only;
    case my17::event_req_toolbar_del:
    {



        int row = ui->mtable->currentIndex().row();

        ui->mtable->removeRow(row);
        MModelDelegate * model = static_cast<MModelDelegate *>(getData());
        model->fields.takeAt(row);



    }
    return my17::todo_done_only;


    }


    return my17::todo_none;

}

DocModelEditor::~DocModelEditor()
{
    delete ui;
}


 void DocModelEditor::setFieldData(int row,MModelFieldDelegate * field)
 {

     ui->mtable->setItem(row,0,new QTableWidgetItem( field->field_name ));
     ui->mtable->setItem(row,1,new QTableWidgetItem( RP->model_field_type_index(field->field_type) ) );
     ui->mtable->setItem(row,2,new QTableWidgetItem(field->field_value));
     ui->mtable->setItem(row,3,new QTableWidgetItem(field->field_descript));

 }
