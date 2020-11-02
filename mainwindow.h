#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QPainter>
//#include <QtGUi>
#include <QApplication>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>

#include "osgwidget.h"

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

public slots:
    void on_actionExit_triggered();

private slots:
    void on_minRadius_valueChanged(int value);

    void on_maxRadius_valueChanged(int value);

    void on_Rcolor_valueChanged(int value);

    void on_Gcolor_valueChanged(int value);

    void on_Bcolor_valueChanged(int value);

    void on_xVelocity_valueChanged(int value);

    void on_yVelocity_valueChanged(int value);

    void on_zVelocity_valueChanged(int value);

    void on_xPosition_valueChanged(int value);

    void on_yPosition_valueChanged(int value);

    void on_zPosition_valueChanged(int value);

private:
    Ui::MainWindowForm * mMainWindowUI;
};

#endif // MAINWINDOW_H
