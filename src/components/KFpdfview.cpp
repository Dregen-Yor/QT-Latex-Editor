#include "KFpdfview.h"
KFpdfview::KFpdfview(QWidget *parent,QPdfDocument *doc):QPdfView(parent){
    setDocument(doc);
    m_pViewManager=qobject_cast<KFViewManager*>(parent);
    m_pMenuRD=new QMenu(this);
    actionCollection()->addAction(KStandardAction::Redisplay,QStringLiteral("pdf_refresh"),this->m_pViewManager->tab(),&KFTabWidget::sendFile);
    m_pMenuRD->addAction(actionCollection()->action(QStringLiteral("pdf_refresh")));
}

KFpdfview::~KFpdfview()=default;

void KFpdfview::mousePressEvent(QMouseEvent *event){
     if (event->button() == Qt::RightButton)
    {
        m_pMenuRD->exec(QCursor::pos());
    }

}