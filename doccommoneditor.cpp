#include "doccommoneditor.h"
#include "ui_doccommoneditor.h"
#include <QLineEdit>
#include <QtGui>
#include <QComboBox>

DocCommonEditor::DocCommonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocCommonEditor)
{
    ui->setupUi(this);

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


    connect(ui->mtable,SIGNAL(cellClicked(int,int)),this,SLOT( slot_onCellSelected(int,int) ) );

}

DocCommonEditor::~DocCommonEditor()
{
    delete adapter;
    delete ui;
}


 my17::TodoResult DocCommonEditor:: todo(my17::Event event,void * arg)
{


     switch( event )
     {
        case my17::event_property_changed:
        {

            for(int k=0;k<adapter->getColCount();k++)
            {

                ui->mtable->setItem(row_selected,k,new QTableWidgetItem( adapter->getValue(row_selected,k) ) );
            }

        }
         return my17::todo_done_only;
        case my17::event_req_toolbar_add:
         {
             ui->mtable->insertRow(ui->mtable->rowCount());
             ui->mtable->selectRow(ui->mtable->rowCount()-1);

             MData * mdata = new MData();
             mdata->key = "key_new";
             mdata->value = "value_new";
             mdata->descript = "descript_new";

             DP->projectinfos.push_back( mdata );

             row_selected = ui->mtable->rowCount()-1;

             for(int k=0;k<adapter->getColCount();k++)
             {

                 ui->mtable->setItem(row_selected,k,new QTableWidgetItem( adapter->getValue(row_selected,k) ) );
             }


         }
        return my17::todo_done_only;
        case my17::event_req_toolbar_del:
        {
             int row = ui->mtable->currentIndex().row();
             ui->mtable->removeRow( row );
             DP->projectinfos.takeAt(row);
        }
         return my17::todo_done_only;

     }


     return my17::todo_none;

 }


 ////////// EditorAdapter
 ///
 ///
  int DocCommonEditor::getEditRowCount()
 {

      NLog::i("getEditRowCount in DocCommonEditor");
      int count = adapter->getColCount();

      return count;

 }
  const QString  DocCommonEditor::getEditDescript()
 {

      return " row edit";

 }
  const QString  DocCommonEditor::getEditTitle(int row)
 {

     return adapter->getHeder(row);

 }
  const QString  DocCommonEditor::getEditValue(int row,int col)
 {


      return adapter->getValue(row_selected,row);

      //return adapter->getValue(row,col);

 }
  QWidget * DocCommonEditor::getEditor(QWidget *parent,int row,int col)
 {

      if( adapter->isEditable(row,col) )
      {
      QLineEdit *m_pTxt = new QLineEdit(parent);
      //connect(m_pTxt, SIGNAL(editingFinished()), this, SLOT(slots_datachanged_name()) );
      return m_pTxt;
      }
      return NULL;

 }
 void DocCommonEditor::setEditorValue(const QString & text,int row,int col)
 {

      //  QLineEdit * m_ptxt =(QLineEdit * ) editor;

      //  m_ptxt->setText( getEditValue(row,col) );
      adapter->onValueChanged(row_selected,row,text);


 }
 ///////////////

 void DocCommonEditor:: slot_onCellSelected(int row,int col)
 {


     NLog::i("on cell selected :%d,%d",row,col);

     row_selected = row;


     MC->sendMessage( my17::event_property_selectd,this);


 }

 void DocCommonEditor::setAdapter(TableAdapter * a)
 {

     adapter = a;

     QStringList headers;

     for(int i=0;i<adapter->getColCount();i++)
     {

         headers.append( adapter->getHeder(i) );
     }

     ui->mtable->setColumnCount( adapter->getColCount() );

     ui->mtable->setHorizontalHeaderLabels(headers);


     for(int i=0;i<adapter->getRowCount();i++)
     {
        for(int k=0;k<adapter->getColCount();k++)
        {

            //NLog::i("get value [%d,%d]:%s",i,k,adapter->getValue(i,k).toStdString().c_str());


            if( k == 0 )
                ui->mtable->insertRow(i);
            ui->mtable->setItem(i,k,new QTableWidgetItem( adapter->getValue(i,k) ) );


        }

     }



 }
