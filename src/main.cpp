// #include "mainwindow.h"
#include "components/kftexmainwindow.h"
#include <klocalizedstring.h>
#include<QDir>
#include<QFile>
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("KFTEX"));
    QDir::addSearchPath("icon",QDir::currentPath() + "/src/theme");
    QFile file(":/src/dark_red.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { file.readAll() };
    a.setStyleSheet(styleSheet);
    KFTEXMainWindow w;
    w.showMaximized(); 
    return a.exec();
}
