#include "viewforms.h"
#include <qevent.h>
#include "lineview.h"
#include "messagecenter.h"
#include "formview.h"
#include "formlineview.h"

ViewForms::ViewForms(QWidget *parent) :
    QWidget(parent),mPressed(false)
{

    mRootView = NULL;
    mRootView = new ViewGroup();



    for(MForm * mf : my17::D::getInstance()->forms )
    {

        FormView * fv = new FormView();
        fv->form = mf;
        fv->viewid = mf->formid;
        fv->initFormData();
        addView(fv);

    }
    for( MLine * ml : DP->formlines )
    {
        FormLineView * lv = new FormLineView();
        lv->viewid = ml->lineid;
        lv->fromid = ml->from;
        lv->toid = ml->to;
        lv->mline = ml;
        lv->line(findViewById(lv->fromid),findViewById(lv->toid) );
        addView(lv);
    }


}

ViewForms::~ViewForms()
{

   // NLog::i("release ViewForms");
    delete mRootView;
   // NLog::i("release ViewForms end");
}

void ViewForms::paintEvent(QPaintEvent * event)
{

    event->accept();
    if( mRootView ){

        QPainter painter(this);
        const QPalette & pal = this->palette();

         mRootView->paint(painter,pal);
    }

}


void ViewForms::resizeEvent(QResizeEvent * qre)
{

    QWidget::resizeEvent(qre);
    qre->accept();
   // NLog::i("ViewForms::resizeEvent");


    try
    {

        if( mRootView )
            this->mRootView->setSize(size().width(),size().height());
    }catch(...)
    {

        NLog::i("resize exception..");
    }

}

void ViewForms::mousePressEvent(QMouseEvent *event)
{


    event->accept();
    if( !mRootView )
        return;


    mPressed_btn_right = (event->button() == Qt::RightButton);
    View * view = mRootView->getViewAtPoint(event->pos(),mPressed_btn_right);
    if( view )
    {

        //if( !mPressed_btn_right )
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

            FormLineView * line = new FormLineView();
            line->setFrom(view);
            line->setPos(view->getRect()->x()+view->getRect()->width()/2,view->getRect()->y()+view->getRect()->height()/2);
            //line->setDefProperty();

            MLine * ml = new MLine();
            ml->lineid = line->viewid;
            ml->from = view->viewid;

            line->mline = ml;

            DP->formlines.push_back( ml );



            mRootView->addView(line);
            mRootView->setCurrentLine(line);
            NLog::i("add lineview....");


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
void ViewForms::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    if( !mRootView )
        return;
    if( mPressed && mPressed_btn_right )
    {


        View * view = mRootView->getViewAtPoint(event->pos(),mPressed_btn_right);


            if( view && !view->isLine() && view != mRootView->getFocus() )
            {

               FormLineView * line = (FormLineView*) mRootView->getCurrentLine();

               if( line )
               {

                   line->setTo(view);
                   line->mline->to = view->viewid;
                   repaint();
               }

            }
            else
            {

                FormLineView * line = (FormLineView*) mRootView->getCurrentLine();

                if( line )
                {
                    mRootView->removeView(line);
                    DP->formlines.takeLast();
                    delete line;

                    repaint();
                    NLog::i("delete lineview....");
                }


            }




        mPressed = false;
        mRootView->setCurrentLine(NULL);


    }


}
void ViewForms::mouseMoveEvent(QMouseEvent *event)
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


