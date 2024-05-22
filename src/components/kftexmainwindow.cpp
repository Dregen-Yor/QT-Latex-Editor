#include "kftexmainwindow.h"
KFTEXMainWindow::KFTEXMainWindow(QWidget* parent )
    : KParts::MainWindow(parent, Qt::Window) 
    , m_wrapper(new KTextEditor::MainWindow(this)){
    m_editor=KTextEditor::Editor::instance();

    // setup the most important widgets
    setupMainWindow();

    // setup the actions
    setupActions();

    setupMenu();
}

void KFTEXMainWindow::setupMainWindow(){
    m_centralWidget = new QFrame(this);
    QVBoxLayout *vlayout =new QVBoxLayout(m_centralWidget);
    vlayout->setContentsMargins(1, 1, 1, 1);
    vlayout->setSpacing(1);
    m_centralWidget->setStyleSheet("border: 1px solid black;");
    m_viewManager =new KFViewManager(m_centralWidget, this);
    // m_viewManager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vlayout->addWidget(m_viewManager);

    m_centralWidget->setLayout(vlayout);
    this->setCentralWidget(m_centralWidget);
}

KTextEditor::Editor *KFTEXMainWindow::getEditor(){
    return m_editor;
}
void KFTEXMainWindow::setupActions(){
    QAction *a=nullptr;
    a=actionCollection()
        ->addAction(KStandardAction::New, QStringLiteral("file_new"), m_viewManager->tab(), &KFTabWidget::openFile);

    a->setShortcut(QKeySequence::New);
    a->setWhatsThis(i18n("Create a new tex file"));
    a=actionCollection()
        ->addAction(KStandardAction::Open, QStringLiteral("file_open"), m_viewManager->tab(), &KFTabWidget::openFile);
    a->setShortcut(QKeySequence::Open);
    a->setWhatsThis(i18n("Open an existing tex file"));

    a=actionCollection()
        ->addAction(KStandardAction::Save, QStringLiteral("file_save"), m_viewManager->tab(), &KFTabWidget::saveFile);
    a->setWhatsThis(i18n("Save the current tex file"));
    a->setShortcut(QKeySequence::Save);
    
}

void KFTEXMainWindow::setupMenu(){
    m_fileMenu=this->menuBar()->addMenu(i18n("&File"));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_new")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_open")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_save")));
}
KFTEXMainWindow::~KFTEXMainWindow()=default;

KFViewManager *KFTEXMainWindow::viewManager(){
    return m_viewManager;
}

QFrame *KFTEXMainWindow::centralWidget() const{
    return m_centralWidget;
}