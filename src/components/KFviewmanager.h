#ifndef KFVIEWMANAGER_H
#define KFVIEWMANAGER_H

#include "kftexmdi.h"
#include "kftexmainwindow.h"
#include "KFeditviewspace.h"
#include <QSplitter>
#include <QLabel>
#include <QPdfView>
#include <QPdfDocument>
#pragma once 
class KFTabWidget;
class KFViewManager: public QSplitter{
    Q_OBJECT
public:    
    KFViewManager(QWidget *parent,KFTEXMainWindow *parentW);
    ~KFViewManager() override;

private slots:
    void showPdf(QFile *file);
    void closePdf();
private:
    std::shared_ptr<QPdfView> m_pdfView=nullptr;
    std::shared_ptr<KFTabWidget> m_tabWidget=nullptr;
    std::shared_ptr<QPdfDocument> m_doc=nullptr;
};
#endif