#include "docurleditor.h"
#include "ui_docurleditor.h"

DocUrlEditor::DocUrlEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocUrlEditor)
{
    ui->setupUi(this);
    QStringList headers;

    headers.append(RP->url_title_index(0));
    headers.append(RP->url_title_index(1));
    headers.append(RP->url_title_index(2));


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

DocUrlEditor::~DocUrlEditor()
{
    delete ui;
}

my17::TodoResult  DocUrlEditor::todo(my17::Event event,void * arg)
{

    switch( event )
    {

        case my17::event_req_toolbar_add:
         {

            NLog::i("add event....");
            ui->mtable->insertRow(ui->mtable->rowCount());
            ui->mtable->selectRow(ui->mtable->rowCount()-1);
            MUrlDelegate * url = DP->newUrl();
            setFieldData( ui->mtable->rowCount()-1, url);

         }
        return my17::todo_done_only;
        case my17::event_req_url_item_data_changed:
        {
            MUrlDelegate * med =(MUrlDelegate *) arg;

            setFieldData( DP->urls.indexOf( med ), med);

        }
        return my17::todo_done_only;

    }


    return my17::todo_none;

}


void DocUrlEditor::setData(void * d)
{


    IExec::setData(d);
    for(int i=0;i<DP->urls.count();i++)
    {
        MUrlDelegate * url = DP->urls.at(i);
       ui->mtable->insertRow(ui->mtable->rowCount());
       setFieldData(ui->mtable->rowCount()-1,url);
    }

}


void DocUrlEditor::setFieldData(int row,MUrlDelegate * url)
{

    ui->mtable->setItem(row,0,new QTableWidgetItem( url->url_name ));
    ui->mtable->setItem(row,1,new QTableWidgetItem( url->url_address) );
    ui->mtable->setItem(row,2,new QTableWidgetItem( url->url_descript));

}


void DocUrlEditor::slot_onTableItemSelected(QTableWidgetItem * item)
{


    MC->sendMessage(my17::event_req_url_item_selected,DP->urls.at(item->row()));


}
