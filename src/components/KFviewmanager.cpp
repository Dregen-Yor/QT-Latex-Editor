#include "KFviewmanager.h"

KFViewManager::KFViewManager(QWidget *parent,KFTEXMainWindow *parentW):QSplitter(parent),
    m_tabWidget(new KFTabWidget(parent,this,parentW->getEditor()))
{
    m_mainwindow=parentW;
    this->addWidget(m_tabWidget);
    // m_doc=new QPdfDocument();
    // this->showPdf(QString("/home/Dregen_Yor/code/higher-design/QT-Latex-Editor/build/src/QT6guide.pdf"));
}
KFViewManager::~KFViewManager()=default;

void KFViewManager::showPdf(QPdfDocument *doc){
    if(m_doc){
        delete m_doc;
    }
    m_doc=doc;
    if(!m_pdfView){
        m_pdfView=new KFpdfview(this,m_doc);
        m_pdfView->setPageMode(QPdfView::PageMode::MultiPage);
        this->addWidget(m_pdfView);
        m_pMenuRD=new QMenu(m_pdfView);
    }
    m_pdfView->setDocument(m_doc);
}
void KFViewManager::closePdf(){
    if(m_pdfView){
        delete(m_pdfView);
        m_pdfView=nullptr;
    }
}
