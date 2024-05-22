#include "KFviewmanager.h"

KFViewManager::KFViewManager(QWidget *parent,KFTEXMainWindow *parentW):QSplitter(parent){
    m_tabWidget=std::make_shared<KFTabWidget>(parent,this,parentW->getEditor());
    this->addWidget(m_tabWidget.get());
}
KFViewManager::~KFViewManager()=default;

void KFViewManager::showPdf(QFile *file){
    if(!m_pdfView){
        m_pdfView=std::make_shared<QPdfView>();
        this->addWidget(m_pdfView.get());
        connect(m_pdfView.get(),&QPdfView::close,this,&KFViewManager::closePdf);
    }
    m_doc= std::make_shared <QPdfDocument>();
    m_doc->load(file);
    m_pdfView->setDocument(m_doc.get());
}
void KFViewManager::closePdf(){
    if(m_pdfView){
        disconnect(m_pdfView.get(),&QPdfView::close,this,&KFViewManager::closePdf);
        m_pdfView=nullptr;
    }
}