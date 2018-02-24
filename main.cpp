#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NLog::i("args: argc:%d argv:%s",argc,argv[0]);

    MainWindow w;

    w.show();

    if( argc > 1 )
        w.setOpenArgs(argv[1]);

    return a.exec();
}
