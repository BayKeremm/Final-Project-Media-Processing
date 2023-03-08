#include "game.h"
#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QtWidgets>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

      MainWindow w;

      Game game = Game(&w);

      w.show();

  return a.exec();
}

