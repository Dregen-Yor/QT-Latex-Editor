#include "mainwindow.h"
#include<iostream>
#include<QDir>
#include<QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::addSearchPath("icon",QDir::currentPath() + "/src/theme");
    
    QFile file(QDir::currentPath() +"/src/dark_red.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { file.readAll() };
    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
