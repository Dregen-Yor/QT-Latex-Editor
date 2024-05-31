#ifndef KFPDFVIEW_H
#define KFPDFVIEW_H

#include <QPdfView>
#include <QWidget>
#include <QMouseEvent>
#include <QMenu>

#include "KFviewmanager.h"
#include <QPdfDocument>
class KFViewManager;
class KFpdfview: public QPdfView,virtual public KParts::PartBase{
    Q_OBJECT
public:
    explicit KFpdfview(QWidget *parent,QPdfDocument *doc);
    ~KFpdfview();
public:
    virtual void mousePressEvent(QMouseEvent *event)override;
    
private:
    QMenu *m_pMenuRD;
    KFViewManager *m_pViewManager;
};
#endif