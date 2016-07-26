#ifndef ViewForms_H
#define ViewForms_H

#include <QWidget>

#include "viewgroup.h"

class ViewForms : public QWidget
{
    Q_OBJECT
public:
    explicit ViewForms(QWidget *parent = 0);

    virtual  ~ViewForms();
protected:
     void paintEvent(QPaintEvent * event);

    virtual void resizeEvent(QResizeEvent * qre);



signals:

public slots:

private:
      ViewGroup * mRootView;
      bool mPressed;
      bool mPressed_btn_right;
public:
    void setRootView(ViewGroup *view)
    {

        mRootView = view;


    }

    void layoutViews() {

        mRootView->setSize(this->rect().width(),this->rect().height());
        mRootView->setPos(0,0);

    }
    ViewGroup * getRootView()
    {

        return mRootView;

    }

    void addView(View * view){


        mRootView->addView(view);

    }


    View * findViewById(const QString & viewid)
    {
        View * view = NULL;
        for(int i=0;i<mRootView->m_children.count();i++)
        {
            view = mRootView->m_children.at(i);
            if( view->viewid == viewid )
            {

                return view;

            }
        }
        return NULL;

    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);



};

#endif // ViewForms_H
