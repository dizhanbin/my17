#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QItemDelegate>
#include "messagecenter.h"

typedef enum{

    index_const,
    index_model,
    index_url,
    index_event,
    index_form,

    index_business,
    index_vars,



}left_0_item_index;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public IExec
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public://IExec implements

    my17::TodoResult todo(my17::Event event, void *arg);
private:
    void init_left_0();
    void init_left_1_items();
    void init_toolbar();
    void init_right_1();
    void do_add_tree_item_for_business();
    void do_add_tree_item_for_model();
    void do_model_data_changed(MModelDelegate * model);
    void do_business_data_changed(MBusinessDelegate * business);
    int do_focus_tab_by_data(void * data,const QString &name);

    virtual void keyReleaseEvent(QKeyEvent * event);

public slots:
    void slot_left_0_item_selected(const QModelIndex & index);
    void slot_left_0_menu_new_bus_triggered(bool checked = false);
    void slot_left_0_menu_new_model_triggered(bool checked = false);
    void slot_left_1_item_double_click(const QModelIndex & index);



    void slot_toolbar_del_click(bool checked = false);
    void slot_toolbar_add_click(bool checked = false);
    void slot_toolbar_save_click(bool checked=false);
    void slot_toolbar_run_click(bool checked=false);


    void slot_tab_close(int index);


public: //qtabledelegate
    /*
        virtual QWidget *    createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        virtual void         setEditorData ( QWidget * editor, const QModelIndex & index ) const;
        virtual void         setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
*/



};







#endif // MAINWINDOW_H
