#include "KFviewmanager.h"

KFViewManager::KFViewManager(QWidget *parent,KFTEXMainWindow *parentW):QSplitter(parent),
    m_tabWidget(new KFTabWidget(parent,this,parentW->getEditor()))
{
    m_mainwindow=parentW;
    this->addWidget(m_tabWidget);
    this->showPdf(QString("/home/Dregen_Yor/code/higher-design/QT-Latex-Editor/build/src/QT6guide.pdf"));
}
KFViewManager::~KFViewManager()=default;

void KFViewManager::showPdf(QString file){
    if(!m_pdfView){
        m_pdfView=new QPdfView();
        m_pdfView->setPageMode(QPdfView::PageMode::MultiPage);
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