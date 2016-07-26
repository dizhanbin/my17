#include "viewdoc.h"
#include <qevent.h>
#include "lineview.h"
#include "messagecenter.h"

ViewDoc::ViewDoc(QWidget *parent) :
    QWidget(parent),mPressed(false)
{

    mRootView = NULL;
  // mRootView = new ViewGroup();

}

ViewDoc::~ViewDoc()
{

    NLog::i("release ViewDoc");
   // delete mRootView;
    NLog::i("release ViewDoc end");
}

void ViewDoc::paintEvent(QPaintEvent * event)
{

    event->accept();
    if( mRootView )
         mRootView->paint(event,this);

}


void ViewDoc::resizeEvent(QResizeEvent * qre)
{

    QWidget::resizeEvent(qre);
    qre->accept();
   // NLog::i("ViewDoc::resizeEvent");


    try
    {

        if( mRootView )
            this->mRootView->setSize(size().width(),size().height());
    }catch(...)
    {

        NLog::i("resize exception..");
    }

}

void ViewDoc::mousePressEvent(QMouseEvent *event)
{


    event->accept();
    if( !mRootView )
        return;


    mPressed_btn_right = (event->button() == Qt::RightButton);
    View * view = mRootView->getViewAtPoint(event->pos(),mPressed_btn_right);
    if( view )
    {

        if( !mPressed_btn_right )
        {
             mRootView->setFocus(view);

             MC->sendMessage(my17::event_req_business_item_selected,view);

        }
        mPressed = true;
        int x = view->getRect()->x();
        int y = view->getRect()->y();
        view->off_width = event->pos().x()-x;
        view->off_height = event->pos().y()-y;

        if( mPressed_btn_right && !view->isLine() )
        {

            LineView * line = new LineView();
            line->setFrom(view);
            line->setPos(view->getRect()->x(),view->getRect()->y());
            line->setDefProperty();


            mRootView->addView(line);
            mRootView->setCurrentLine(line);



        }


        repaint();

    }
    else
    {
        mPressed = false;
        mPressed_btn_right = false;
        mRootView->setFocus(NULL);
        repaint();
    }

}
void ViewDoc::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    if( !mRootView )
        return;
    if( mPressed && mPressed_btn_right )
    {


        View * view = mRootView->getViewAtPoint(event->pos(),mPressed_btn_right);


            if( view && !view->isLine() )
            {

               LineView * line = (LineView*) mRootView->getCurrentLine();

               if( line )
               {

                   line->setTo(view);
                   repaint();
               }

            }
            else
            {

                LineView * line = (LineView*) mRootView->getCurrentLine();

                if( line )
                {
                    mRootView->removeView(line);
                    delete line;
                    repaint();
                }

            }




        mPressed = false;
        mRootView->setCurrentLine(NULL);


    }


}
void ViewDoc::mouseMoveEvent(QMouseEvent *event)
{


    event->accept();
    if( !mRootView )
        return;
    if( mPressed )
    {

        if( !mPressed_btn_right )
        {

            View * focus = mRootView->getFocus();
            if( focus && !focus->isLine() )
            {
                focus->setPos(event->pos().x()-focus->off_width,event->pos().y()-focus->off_height);
                repaint();
            }
        }
        else
        {
            LineView * line =(LineView*) mRootView->getCurrentLine();
            if( line )
            {
                line->setTo(event->pos().x(),event->pos().y());
                repaint();
            }
        }


    }

}


