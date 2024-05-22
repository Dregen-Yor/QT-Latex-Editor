#include "kftexmainwindow.h"
KFTEXMainWindow::KFTEXMainWindow()
    : KFMDI::MainWindow(nullptr)
    , m_wrapper(new KTextEditor::MainWindow(this)){
    m_editor=KTextEditor::Editor::instance();

    // setup the most important widgets
    setupMainWindow();

    // setup the actions
    setupActions();
}


void KFTEXMainWindow::setupMainWindow(){
    m_viewManager = std::make_shared <KFViewManager>(this, this);
    setCentralWidget(m_viewManager.get());
    // centralWidget()->layout()->addWidget(m_viewManager.get());
}

KTextEditor::Editor *KFTEXMainWindow::getEditor(){
    return m_editor;
}
void KFTEXMainWindow::setupActions(){

}
KFTEXMainWindow::~KFTEXMainWindow()=default;