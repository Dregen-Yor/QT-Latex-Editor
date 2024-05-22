#ifndef KFTEXMDI_H
#define KFTEXMDI_H
#include <KParts/MainWindow>
#include <KTextEditor/Plugin>
#include <KMultiTabBar>
#include <KActionMenu>
#include <KToggleAction>

#include <QWidget>
#include <QToolBar>
#include <QSplitter>
#include <QFrame>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QEvent>
#include <QSplitter>
#include <QPointer>
#include <QDomDocument>

#include <memory>
#include "KFviewmanager.h"
#pragma once 
namespace KFMDI{    

class MainWindow: public KParts::MainWindow{
    Q_OBJECT
public:    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    QWidget *centralWidget() const;

    QWidget *createContainer(QWidget *parent, int index, const QDomElement &element, QAction *&containerAction) override;
private:
    /**
     * widget, which is the central part of the
     * main window ;)
     */
    std::shared_ptr<QFrame> m_centralWidget;


};

class kftoolbar: public QToolBar{
    Q_OBJECT
public:
    kftoolbar(QWidget *parent=nullptr);
    ~kftoolbar()override;
};
}
#endif // KFTEXMDI_H