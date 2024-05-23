#include "KFpdfview.h"
KFpdfview::KFpdfview(QWidget *parent,QPdfDocument *doc):QPdfView(parent){
    setDocument(doc);
    m_pMenuRD=new QMenu(this);
    // actionCollection()->addAction(KStandardAction::Close,QStringLiteral("pdf_close"),this,&KFViewManager::closePdf);
    // m_pMenuRD->addAction(actionCollection()->action(QStringLiteral("pdf_close")));
}

KFpdfview::~KFpdfview()=default;

void KFpdfview::mousePressEvent(QMouseEvent *event){
     if (event->button() == Qt::RightButton)
    {
        m_pMenuRD->exec(QCursor::pos());
    }

}