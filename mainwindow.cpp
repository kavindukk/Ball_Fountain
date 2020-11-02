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

void MainWindow::on_minRadius_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_radius((double)value/1000., 0);
}

void MainWindow::on_maxRadius_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_radius((double)value/1000., 1);
}

void MainWindow::on_Rcolor_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_color((double)value/1000.,0);
}

void MainWindow::on_Gcolor_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_color((double)value/1000.,1);
}

void MainWindow::on_Bcolor_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_color((double)value/1000.,2);
}

void MainWindow::on_xVelocity_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_velocity((double)value/100.,0);
}

void MainWindow::on_yVelocity_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_velocity(double(value)/100.,1);
}

void MainWindow::on_zVelocity_valueChanged(int value)
{
 mMainWindowUI->widget->set_ball_velocity((double)value/100.,2);
}

void MainWindow::on_xPosition_valueChanged(int value)
{
   mMainWindowUI->widget->set_ball_origin((double)value/1000.,0);
}

void MainWindow::on_yPosition_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_origin((double)value/1000.,1);
}

void MainWindow::on_zPosition_valueChanged(int value)
{
    mMainWindowUI->widget->set_ball_origin(-3.+(double)value/1000.,2);
}
