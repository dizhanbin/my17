#include "docformeditor.h"
#include "ui_docformeditor.h"
#include "formview.h"
DocFormEditor::DocFormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocFormEditor)
{
    ui->setupUi(this);

    mViewForm = new ViewForms(ui->mScroll);
    mViewForm->setGeometry(QRect(0, 0, 1200, 1200));
    setData((void*)1);

}

DocFormEditor::~DocFormEditor()
{

    delete mViewForm;
    delete ui;
}

void DocFormEditor::resizeEvent(QResizeEvent * qre)
{


   mViewForm->setGeometry(0,0,size().width(),size().height());
   mViewForm->repaint();
}


my17::TodoResult  DocFormEditor::todo(my17::Event event,void * arg)
{

    switch( event )
    {

        case my17::event_req_toolbar_add :
        {


            MForm * mform = new MForm();
            mform->formid = my17::R::getInstance()->getId();
            DP->forms.push_back( mform );

            FormView * fv = new FormView();

            MProperty * mp0 = new MProperty();
            mp0->p_name = "name";
            mp0->p_title = "事件";
            mp0->p_type = 1;
            mp0->p_args = "$event";

            MProperty * mp1 = new MProperty();
            mp1->p_name = "descript";
            mp1->p_title = "描述";
            mp1->p_type = 0;

            MProperty * mp2 = new MProperty();
            mp2->p_name = "android";
            mp2->p_title = "androd类";
            mp2->p_type = 0;

            MProperty * mp3 = new MProperty();
            mp3->p_name = "ios";
            mp3->p_title = "ios类";
            mp3->p_type = 0;



            mform->properties.push_back(mp0);
            mform->properties.push_back(mp2);
            mform->properties.push_back(mp3);
            mform->properties.push_back(mp1);

            fv->form = mform;

            fv->initFormData();


            mViewForm->addView(fv);

            mViewForm->repaint();
            NLog::i("add in docform...");

        }
        return my17::todo_done_only;
        case my17::event_req_toolbar_del:
        {




            View * view = mViewForm->getRootView()->getFocus();
            if( view )
            {

                void * data = view->getData();
                if( data )
                {
                    MForm * mf = static_cast<MForm*>(data);
                    if( mf )
                    {

                        for(int i=DP->formlines.count()-1;i>-1;i--)
                        {
                            MLine * line = DP->formlines.at(i);
                            if( line->from == mf->formid || line->to == mf->formid )
                            {
                                DP->formlines.takeAt(i);
                            }

                        }

                        int index = DP->forms.indexOf( mf );
                        if( index > -1 )
                            DP->forms.takeAt(index);

                    }

                }

                mViewForm->getRootView()->removeView(view);
                delete view;
                mViewForm->repaint();
            }



        }
        return my17::todo_done_only;

    }


    return my17::todo_none;
}
