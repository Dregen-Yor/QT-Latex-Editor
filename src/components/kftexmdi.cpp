#include "kftexmdi.h"
namespace KFMDI {

MainWindow::MainWindow(QWidget* parent)
    : KParts::MainWindow(parent, Qt::Window) {
    m_centralWidget=std::make_shared<QFrame>();
    setCentralWidget(m_centralWidget.get());
    std::shared_ptr<QVBoxLayout> vlayout = std::make_shared<QVBoxLayout>(m_centralWidget.get());
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);

    // // create the main widget
    
    // // top level vbox for all stuff + bottom bar
    // std::shared_ptr<QVBoxLayout> toplevelVBox =
    //     std::make_shared<QVBoxLayout>(hb);
    // toplevelVBox->setContentsMargins(0, 0, 0, 0);
    // toplevelVBox->setSpacing(0);

    // // hbox for all splitters and other side bars
    // std::shared_ptr<QHBoxLayout> hlayout = std::make_shared<QHBoxLayout>();
    // hlayout->setContentsMargins(0, 0, 0, 0);
    // hlayout->setSpacing(0);
    // toplevelVBox->addLayout(hlayout.get());

    // m_hSplitter = std::make_shared<QSplitter>(Qt::Horizontal, hb);
    // hlayout->addWidget(m_hSplitter.get());

    // std::shared_ptr<QFrame> vb = std::make_shared<QFrame>(m_hSplitter.get());
    // QVBoxLayout* vlayout = new QVBoxLayout(vb.get());
    // vlayout->setContentsMargins(0, 0, 0, 0);
    // vlayout->setSpacing(0);


    // m_centralWidget = std::make_shared<QWidget>(m_vSplitter.get());
    // m_centralWidget->setLayout(new QVBoxLayout);
    // m_centralWidget->layout()->setSpacing(0);
    // m_centralWidget->layout()->setContentsMargins(0, 0, 0, 0);

}

MainWindow::~MainWindow() {}
QWidget* MainWindow::centralWidget() const {
    return m_centralWidget.get();
}

QWidget* MainWindow::createContainer(QWidget* parent,
                                     int index,
                                     const QDomElement& element,
                                     QAction*& containerAction) {
    // ensure we don't have toolbar accelerators that clash with other stuff
    QWidget* createdContainer = KParts::MainWindow::createContainer(
        parent, index, element, containerAction);
    return createdContainer;
}

};  // namespace KFMDI