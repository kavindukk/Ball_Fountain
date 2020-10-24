#include "mainwindow.h"
#include <QApplication>

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
