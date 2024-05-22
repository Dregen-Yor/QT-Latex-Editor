#ifndef KFVIEWMANAGER_H
#define KFVIEWMANAGER_H

#include <QLabel>
#include <QPdfDocument>
#include <QPdfView>
#include <QString>
#include <QSplitter>
#include "KFeditviewspace.h"
#include "kftexmainwindow.h"
#pragma once
class KFTabWidget;
class KFViewManager : public QSplitter {
    Q_OBJECT
   public:
    KFViewManager(QWidget* parent, KFTEXMainWindow* parentW);
    ~KFViewManager() override;
    KFTabWidget* tab() { return m_tabWidget; }
    KFTEXMainWindow* mainwindow() { return m_mainwindow; }
   private slots:
    void showPdf(QString file);
    void closePdf();

   private:
    QPdfView* m_pdfView = nullptr;
    KFTabWidget* m_tabWidget = nullptr;
    QPdfDocument* m_doc = nullptr;
    KFTEXMainWindow* m_mainwindow;
};
#endif