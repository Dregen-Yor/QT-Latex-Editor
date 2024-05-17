#include "mainwindow.h"
#include "./assets/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // this -> showFullScreen();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

