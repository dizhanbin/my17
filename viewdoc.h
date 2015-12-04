#ifndef VIEWDOC_H
#define VIEWDOC_H

#include <QWidget>

#include "viewgroup.h"

class ViewDoc : public QWidget
{
    Q_OBJECT
public:
    explicit ViewDoc(QWidget *parent = 0);

    virtual  ~ViewDoc();
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



protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);



};

#endif // VIEWDOC_H
