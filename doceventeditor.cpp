#include "doceventeditor.h"
#include "ui_doceventeditor.h"
#include "nlog.h"


DocEventEditor::DocEventEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocEventEditor)
{
    ui->setupUi(this);
    QStringList headers;

    headers.append(RP->event_title_index(0));
    headers.append(RP->event_title_index(1));
    headers.append(RP->event_title_index(2));


    ui->mtable->setColumnCount(3);
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

DocEventEditor::~DocEventEditor()
{
    delete ui;
}


my17::TodoResult DocEventEditor::todo(my17::Event event,void * arg)
{


    switch( event )
    {

        case my17::event_req_toolbar_add:
         {

            NLog::i("add event....");
            ui->mtable->insertRow(ui->mtable->rowCount());
            ui->mtable->selectRow(ui->mtable->rowCount()-1);

            MEventDelegate * med = DP->newEvent();

            setFieldData( ui->mtable->rowCount()-1, med);
         }
        return my17::todo_done_only;
        case my17::event_req_event_item_data_changed:
        {
            MEventDelegate * med =(MEventDelegate *) arg;

            setFieldData( DP->events.indexOf( med ), med);

        }
        return my17::todo_done_only;

    }


}


void DocEventEditor::setFieldData(int row,MEventDelegate * event)
{

    ui->mtable->setItem(row,0,new QTableWidgetItem( event->event_name ));
    ui->mtable->setItem(row,1,new QTableWidgetItem( RP->event_type_index(event->event_type) ) );
    ui->mtable->setItem(row,2,new QTableWidgetItem(event->event_descript));

}


void DocEventEditor::slot_onTableItemSelected(QTableWidgetItem * item)
{



    MC->sendMessage(my17::event_req_event_item_selected,DP->getEvent(item->row()) );


}
