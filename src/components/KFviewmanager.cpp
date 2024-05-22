#include "KFviewmanager.h"

KFViewManager::KFViewManager(QWidget *parent,KFTEXMainWindow *parentW):QSplitter(parent),
    m_tabWidget(new KFTabWidget(parent,this,parentW->getEditor()))
{
    m_mainwindow=parentW;
    this->addWidget(m_tabWidget);
}
KFViewManager::~KFViewManager()=default;

void KFViewManager::showPdf(QFile *file){
    if(!m_pdfView){
        m_pdfView=new QPdfView();
        this->addWidget(m_pdfView);
        connect(m_pdfView,&QPdfView::close,this,&KFViewManager::closePdf);
    }
    m_doc=new QPdfDocument();
    m_doc->load(file);
    m_pdfView->setDocument(m_doc);
}
void KFViewManager::closePdf(){
    if(m_pdfView){
        disconnect(m_pdfView,&QPdfView::close,this,&KFViewManager::closePdf);
        m_pdfView=nullptr;
    }
}