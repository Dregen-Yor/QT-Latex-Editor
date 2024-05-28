#ifndef KFVIEWMANAGER_H
#define KFVIEWMANAGER_H

#include <QLabel>
#include <QPdfDocument>
#include <KActionCollection>
#include <KActionMenu>
#include <QPdfView>
#include <QString>
#include <QSplitter>

#include "KFeditviewspace.h"
#include "KFpdfview.h"
#include "kftexmainwindow.h"
#pragma once
class KFTabWidget;
class KFpdfview;
class KFViewManager : public QSplitter {
    Q_OBJECT
   public:
    KFViewManager(QWidget* parent, KFTEXMainWindow* parentW);
    ~KFViewManager() override;
    KFTabWidget* tab() { return m_tabWidget; }
    KFTEXMainWindow* mainwindow() { return m_mainwindow; }
   public slots:
    void showPdf(QPdfDocument *doc);
    void closePdf();

   private:
    KFpdfview* m_pdfView = nullptr;
    KFTabWidget* m_tabWidget = nullptr;
    QPdfDocument* m_doc = nullptr;
    QMenu *m_pMenuRD=nullptr;
    QAction *a=nullptr;
    KFTEXMainWindow* m_mainwindow;
};
#endif