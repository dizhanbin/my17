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


    ui->mScroll->setWidget(mViewDoc);

    mViewDoc->setGeometry(QRect(0, 0, 2000, 2000));

  //  ui->mScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->mScroll->setWidgetResizable(false);


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


    int w = mViewDoc->rect().width() > mbd->viewgroup->max_width ?  mViewDoc->rect().width() : mbd->viewgroup->max_width;
    int h = mViewDoc->rect().height()> mbd->viewgroup->max_height? mViewDoc->rect().height() : mbd->viewgroup->max_height;


    mViewDoc->setGeometry(0,0,w,h);



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



          MC->sendMessage( event_req_business_item_selected,NULL);



        }
            return my17::todo_done;


    }



    return  my17::todo_none;
}


 void DocBusinessEditor::resizeEvent(QResizeEvent * qre)
 {


   // mViewDoc->setGeometry(0,0,size().width(),size().height());
   // mViewDoc->repaint();
   // ui->mScroll->setGeometry(0,0,size().width()-100,size().height()-100);




 }
void DocBusinessEditor::keyPressEvent(QKeyEvent *event)
 {



    if( event->type() == QKeyEvent::KeyPress )
    switch (event->key()) {

        case Qt::Key_Backspace:
            todo(my17::Event::event_req_toolbar_del,NULL);
            NLog::i("key press delete");
        case Qt::Key_C:
        {

          if( event->modifiers()  == Qt::ControlModifier )
          {
               // NLog::i("key press key c :%d  :%d :%d  modifiers:%d",event->nativeScanCode(),event->nativeVirtualKey(),event->nativeModifiers(),event->modifiers());

              View * view = mViewDoc->getRootView()->getFocus();

              if( view ){

                  IconView * icon = dynamic_cast<IconView*>(view);
                  if( icon ){


                        DP->copyvalue = icon->copy();


                  }

              }


          }

        }
        break;

    case Qt::Key_V:
        {

            if( event->modifiers()  == Qt::ControlModifier )
            {

                if( DP->copyvalue ){
                    IconView * icon = (IconView*) DP->copyvalue ;
                    if( icon ){
                        mViewDoc->addView(icon );
                        mViewDoc->getRootView()->setFocus(icon);
                        mViewDoc->repaint();
                        DP->copyvalue = NULL;
                    }
                }

            }


        }
        break;




    default:
        break;
    }

 }
