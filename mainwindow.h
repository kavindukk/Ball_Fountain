#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QPainter>
#include <QtGUi>
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

private:
    Ui::MainWindowForm * mMainWindowUI;
};

#endif // MAINWINDOW_H
