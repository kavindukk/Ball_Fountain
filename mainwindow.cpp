#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent}

{
    OSGWidget *osgwidget = new OSGWidget(this);
    this->setCentralWidget(osgwidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
