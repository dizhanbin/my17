#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my17.h"
#include "nlog.h"
#include <QStandardItemModel>
#include "docbusinesseditor.h"
#include "docmodeleditor.h"
#include "doceventeditor.h"
#include "doceventeditor.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


 //  my17::event ev = my17::event_req_view_add;



    MessageCenter::getInstence()->register_todo(this);


    MessageCenter::getInstence()->sendMessage(my17::event_req_menu_init,NULL);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete my17::D::getInstance();
    delete my17::R::getInstance();
    delete MessageCenter::getInstence();
    NLog::i("release MainWindow end");

}

void MainWindow::init_left_0_menu()
{


    QStandardItemModel * model = new QStandardItemModel();
    QStandardItem* item00 = new QStandardItem("数据对象");
    model->insertRow(0,item00);

    QStandardItem* item10 = new QStandardItem("事件");
    model->insertRow(1,item10);

    QStandardItem* item20 = new QStandardItem("业务");
    model->insertRow(2,item20);


    ui->left_0->setHeaderHidden(true);
    ui->left_0->setModel(model);
    ui->left_0->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QAction *action_newmodel = new QAction("  新建数据对象  ", this);
    QAction *action_newevent = new QAction("  新建事件  ", this);
    QAction *action_newbusiness = new QAction("  新建业务流程  ", this);


    ui->left_0->addAction(action_newmodel);
    ui->left_0->addAction(action_newevent);
    ui->left_0->addAction(action_newbusiness);
    ui->left_0->setContextMenuPolicy(Qt::ActionsContextMenu);


    connect(ui->left_0,SIGNAL(clicked(const QModelIndex& )),this,SLOT(slot_left_0_item_selected(const QModelIndex & )));


    connect(action_newbusiness, SIGNAL(triggered(bool)), this, SLOT(slot_left_0_menu_new_bus_triggered(bool)) );

    connect(action_newmodel, SIGNAL(triggered(bool)), this, SLOT(slot_left_0_menu_new_model_triggered(bool)) );





    // NLog::i("menuconnect");





}

void MainWindow::init_right_1()
{

    QStringList headers;
    headers.append("字段");
    headers.append("值");

    ui->right_bottom->setColumnCount(2);
    ui->right_bottom->setHorizontalHeaderLabels(headers);

    ui->right_bottom->horizontalHeader()->setStretchLastSection(true);

    ui->right_bottom->horizontalHeader()->sectionResizeMode( QHeaderView::Stretch);
    QHeaderView *headerView =  ui->right_bottom->verticalHeader();
    headerView->setHidden(true);


}

void MainWindow::init_toolbar()
{

    QAction * action_del = new QAction(" 删除 ", this);
    action_del->setIcon(  QIcon(QPixmap(  ":image/icon_del.png" ))  );
    ui->toolBar->addAction(action_del);

    QAction * action_add = new QAction(" 添加 ", this);
    action_add->setIcon(  QIcon(QPixmap(  ":image/icon_add.png" ))  );
    ui->toolBar->addAction(action_add);

    connect(action_del, SIGNAL(triggered(bool)), this, SLOT(slot_toolbar_del_click(bool)) );
    connect(action_add, SIGNAL(triggered(bool)), this, SLOT(slot_toolbar_add_click(bool)) );


}

void MainWindow::init_left_1_items()
{


    QStandardItemModel * model = new QStandardItemModel();



    const QVector<MElement*> &vecs = my17::R::getInstance()->elements;

    for(int i=0;i<vecs.size();i++)
    {

        MElement * e = vecs.at(i);

        QStandardItem* item = new QStandardItem(    e->name  );
        item->setIcon( QIcon(QPixmap(   e->iconpath  )) );
        model->insertRow(i,item);

    }



    ui->left_1->setModel(model);
    ui->left_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->left_1,SIGNAL(doubleClicked(const QModelIndex)),SLOT(slot_left_1_item_double_click(const QModelIndex &)) );

}


void MainWindow::slot_left_1_item_double_click(const QModelIndex & index)
{

    NLog::i("business item double click..row:%d col:%d",index.row(),index.column());


    int  ele = index.row();

    MessageCenter::getInstence()->sendMessage(my17::event_req_business_item_double_click,&ele);
}


void MainWindow::slot_left_0_item_selected(const QModelIndex & index)
{


   switch( index.parent().row() )
   {

        case -1:
       {
            if( index.row() == 1 )
            {

                NLog::i("show event editor");

               int index = do_focus_tab_by_data(&DP->events,"事件");
               if( index == -1 )
               {

                    DocEventEditor * doc = new DocEventEditor();
                    ui->center_document->addTab(doc,"事件");
                    doc->setData(&DP->events);
                    ui->center_document->setCurrentWidget(doc);

               }


            }

       }
       return;
        case 0://model
        {
            MModelDelegate * mm =   my17::D::getInstance()->getModel(index.row());
            MessageCenter::getInstence()->sendMessage( my17::event_req_model_selected,mm  );
        }
            return;


        case 2://business
       {

           MBusinessDelegate * mb = DP->getBusiness(index.row());

           MC->sendMessage(my17::event_req_business_selected,mb);


       }
        break;


   }


   // NLog::i("menu click row: %d,col :%d parent:row:%d",index.row(),index.column(),index.parent().row());

}

void MainWindow::slot_left_0_menu_new_bus_triggered(bool checked)
{

    //NLog::i("menu click%d",checked);

    MessageCenter::getInstence()->sendMessage(my17::event_req_add_business);


}

void MainWindow::slot_left_0_menu_new_model_triggered(bool checked)
{



    MessageCenter::getInstence()->sendMessage(my17::event_req_add_model);


}

 void MainWindow::slot_toolbar_del_click(bool checked)
 {

       MessageCenter::getInstence()->sendMessage(my17::event_req_toolbar_del);

 }

 void MainWindow::slot_toolbar_add_click(bool checked)
 {

     MessageCenter::getInstence()->sendMessage(my17::event_req_toolbar_add);

 }

my17::TodoResult MainWindow::todo(my17::Event event, void *arg)
{

    NLog::i("MainWindow::todo event:%d",event);

    switch( event )
    {

        case my17::event_req_menu_init:
            init_left_0_menu();
            init_left_1_items();
            init_toolbar();
            init_right_1();

            return my17::todo_done_only;
        case my17::event_req_add_business:
            do_add_tree_item_for_business();
            return my17::todo_done_only;
        case my17::event_req_add_model:

            do_add_tree_item_for_model();
            return my17::todo_done_only;
        case my17::event_req_model_selected:
        {

            while( ui->right_bottom->rowCount()>0 )
                ui->right_bottom->removeRow(0);
            MModelDelegate * mm  = (MModelDelegate*)arg;
            ui->right_bottom->insertRow(0);
            ui->right_bottom->setItemDelegate(mm);

            do_focus_tab_by_data(mm,mm->name);

        }
            return my17::todo_done_only;
        case my17::event_req_business_selected:
        {

            while( ui->right_bottom->rowCount()>0 )
                ui->right_bottom->removeRow(0);
            MBusinessDelegate * mm  = (MBusinessDelegate*)arg;
            ui->right_bottom->insertRow(0);
            ui->right_bottom->setItemDelegate(mm);

            do_focus_tab_by_data(mm,mm->name);

        }
            return my17::todo_done_only;
        case my17::event_req_model_data_changed:
        {


            MModelDelegate * d = (MModelDelegate*)arg;
            do_model_data_changed(d);


        }
            return my17::todo_done_only;
         case my17::event_req_business_data_changed:
        {
            MBusinessDelegate * md = (MBusinessDelegate*)arg;
            do_business_data_changed(md);
        }
            return my17::todo_done_only;
        case my17::event_req_model_field_selected:
        {
            MModelFieldDelegate * mm  = (MModelFieldDelegate*)arg;
            while( ui->right_bottom->rowCount()>0 )
                ui->right_bottom->removeRow(0);

            for(int i=0;i<4;i++)
                ui->right_bottom->insertRow(0);

            ui->right_bottom->setItemDelegate(mm);

        }
            return my17::todo_done_only;
        case my17::event_req_event_item_selected:
        {
            MEventDelegate * med = (MEventDelegate *)arg;
             while( ui->right_bottom->rowCount()>0 )
                  ui->right_bottom->removeRow(0);
             for(int i=0;i<3;i++)
                 ui->right_bottom->insertRow(0);

             ui->right_bottom->setItemDelegate(med);
        }

        return my17::todo_done_only;
    }




   QWidget * widget =  ui->center_document->currentWidget();


   IExec * exe = dynamic_cast<IExec*>(widget);



    if( exe )
    {
      return  exe->todo(event,arg);
    }



    return my17::todo_none;

}


int MainWindow::do_focus_tab_by_data(void * data,const QString &name)
{


    for(int i=0;i<ui->center_document->count() ;i++)
    {
        IExec * exec = dynamic_cast<IExec*>(ui->center_document->widget( i));

        if( exec )
        {
            if( exec->getData() == data )
            {
                ui->center_document->setCurrentIndex(i);
                ui->center_document->setTabText(i,name);
                return i;

            }

        }

    }
    return -1;

}


void MainWindow::do_add_tree_item_for_business()
{


    MBusinessDelegate * mb = my17::D::getInstance()->newBusiness();

    QStandardItemModel * model = (QStandardItemModel*)ui->left_0->model();
    QStandardItem * item = model->item(2);
    QStandardItem* item_new = new QStandardItem(mb->name);
    item->insertRow(item->rowCount(),item_new);
    ui->left_0->setCurrentIndex( item_new->index() );

    DocBusinessEditor * doc = new DocBusinessEditor();
    doc->setData( mb );
    ui->center_document->addTab(doc,mb->name);

    MC->sendMessage(my17::event_req_business_selected,mb);
}


void MainWindow::do_add_tree_item_for_model()
{

    QStandardItemModel * model = (QStandardItemModel*)ui->left_0->model();
    QStandardItem * item = model->item(0);

    MModelDelegate * mm =  my17::D::getInstance()->newModel();

    QStandardItem* item20 = new QStandardItem( mm->name);
    item->insertRow(item->rowCount(),item20);
    ui->left_0->setCurrentIndex( item20->index() );

    DocModelEditor * doc = new DocModelEditor();
    ui->center_document->addTab(doc,mm->name);
    doc->setData(mm);

    MessageCenter::getInstence()->sendMessage(my17::event_req_model_selected,mm);

}

void MainWindow::do_model_data_changed(MModelDelegate * mmd)
{


     int index = my17::D::getInstance()->getIndex(mmd);

     NLog::i("do_model_data_changed name:%s index:%d",mmd->name.toStdString().c_str(),index);


     QStandardItemModel * model = (QStandardItemModel*)ui->left_0->model();

     QStandardItem * item =  model->item(0)->child(index);

     NLog::i("do_model_data_changed name item:%d count:%d",item,model->item(0)->rowCount());

    if( item )
        item->setText( mmd->name  );

    do_focus_tab_by_data(mmd,mmd->name);



}

void MainWindow::do_business_data_changed(MBusinessDelegate * business)
{

    int index = DP->getIndex(business);


    QStandardItemModel * model = (QStandardItemModel*)ui->left_0->model();

    QStandardItem * item =  model->item(2)->child(index);

     if( item )
       item->setText( business->name  );

    do_focus_tab_by_data(business,business->name);


}
