#include "mainwindow.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QTimer>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

