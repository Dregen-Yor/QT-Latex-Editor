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
    m_fileOpenRecent=KStandardAction::openRecent(m_viewManager->tab(),[this](const QUrl &url) {
            m_viewManager->tab()->openRecent(url);
        },
        this);
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

    a=actionCollection()
        ->addAction(KStandardAction::Close,QStringLiteral("pdf_close"),m_viewManager,&KFViewManager::closePdf);
    a->setWhatsThis(i18n("close the pdf preview"));

    a=actionCollection()
        ->addAction(KStandardAction::Clear,QStringLiteral("pdf_run"),m_viewManager->tab(),&KFTabWidget::sendFile);
    a->setWhatsThis(i18n("Send tex to the serve and open it"));

    a=actionCollection()
        ->addAction(KStandardAction::AboutApp,QStringLiteral("about_app"),this);
    a->setWhatsThis(i18n("The infomation about this app"));

    a=actionCollection()
        ->addAction(KStandardAction::AboutKDE,QStringLiteral("about_KDE"),this);
    a->setWhatsThis(i18n("The information about KDE"));
    
}

void KFTEXMainWindow::setupMenu(){
    m_fileMenu=this->menuBar()->addMenu(i18n("&File"));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_new")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_open")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_save")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("pdf_close")));
    m_fileMenu->addAction(m_fileOpenRecent);
    m_runMenu=this->menuBar()->addMenu(i18n("Run"));
    m_runMenu->addAction(actionCollection()->action(QStringLiteral("pdf_run")));
}
KFTEXMainWindow::~KFTEXMainWindow()=default;

KFViewManager *KFTEXMainWindow::viewManager(){
    return m_viewManager;
}

QFrame *KFTEXMainWindow::centralWidget() const{
    return m_centralWidget;
}
void KFTEXMainWindow::addRecentOpenedFile(const QUrl &url){
    if (url.isEmpty()) {
        return;
    }
    m_fileOpenRecent->addUrl(url);
}