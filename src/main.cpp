// #include "mainwindow.h"
#include <klocalizedstring.h>
#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QString>
#include "components/kftexmainwindow.h"

#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    KAboutData aboutData(
        QStringLiteral("KFTex"), i18n("KFTex"), QStringLiteral("0.1.0"),
        i18n("KFTex - Text Editor"), KAboutLicense::LGPL_V2,
        i18n("(c) 2024-2025 The Kate Authors"),
        // use the other text field to get our mascot into the about dialog
        QStringLiteral(
            "<img height=\"362\" width=\"512\" />"),
        QStringLiteral("https://kate-editor.org"));
    aboutData.setOrganizationDomain(QByteArray("kde.org"));
    aboutData.setProductName(QByteArray("KFTex"));
    aboutData.addAuthor(i18n("孙更欣"), i18n("Maintainer"), QStringLiteral("202322460126@mail.sdu.edu.cn"), QStringLiteral("https://cullmann.io"));
    QApplication a(argc, argv);
    KAboutData::setApplicationData(aboutData);
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("KFTEX"));


    KFTEXMainWindow w;
    w.showMaximized();
    google::ShutdownGoogleLogging();
    return a.exec();
}
