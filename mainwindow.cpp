#include "mainwindow.h"
#include "ui_mainwindowform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}

{
    resize(800,600);
    mMainWindowUI->setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
