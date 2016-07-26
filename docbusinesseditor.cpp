#include "docbusinesseditor.h"
#include "ui_docbusinesseditor.h"
#include "my17.h"
#include "iconview.h"

using namespace my17;

DocBusinessEditor::DocBusinessEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocBusinessEditor)
{
    ui->setupUi(this);

    mViewDoc = new ViewDoc(ui->mScroll);




    mViewDoc->setGeometry(QRect(0, 0, 800, 900));



}

DocBusinessEditor::~DocBusinessEditor()
{

    delete mViewDoc;
    delete ui;
}

void DocBusinessEditor::setData(void *d)
{

    IExec::setData(d);
    MBusinessDelegate * mbd = (MBusinessDelegate *)d;

   // mbd->viewgroup = mViewDoc->getRootView();


    mViewDoc->setRootView( mbd->viewgroup );

}

 my17::TodoResult  DocBusinessEditor::todo(my17::Event event,void * arg)
{

    NLog::i("todo in DocBusinessEditor.");

    switch( event )
    {
        case my17::event_req_business_item_double_click:
        {
            int * index = (int*)arg;

            MElement * e = R::getInstance()->elements.at(*index);

            IconView * view = new IconView(     );
            view->m_element_id = e->ele_id;

            view->newProperties(e->properties);

            mViewDoc->addView(view );
            mViewDoc->repaint();

        }
            return my17::todo_done;
        case my17::event_req_toolbar_del:
        {
           View * view = mViewDoc->getRootView()->getFocus();
           if( view )
           {

               mViewDoc->getRootView()->removeView(view);
               delete view;
               mViewDoc->repaint();
           }




        }
            return my17::todo_done;


    }



    return  my17::todo_none;
}


 void DocBusinessEditor::resizeEvent(QResizeEvent * qre)
 {


    mViewDoc->setGeometry(0,0,size().width(),size().height());
    mViewDoc->repaint();
 }
