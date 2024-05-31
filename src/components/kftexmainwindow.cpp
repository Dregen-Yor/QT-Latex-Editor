#include "kftexmainwindow.h"
KFTEXMainWindow::KFTEXMainWindow(QWidget* parent )
    : KParts::MainWindow(parent, Qt::Window) 
    , m_wrapper(new KTextEditor::MainWindow(this)){
    m_editor=KTextEditor::Editor::instance();
    toolbar=addToolBar("Toolbar");
    toolbar->setFixedHeight(50);
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

    // a->setShortcut(QKeySequence::New);
    a->setWhatsThis(i18n("Create a new tex file"));
    a=actionCollection()
        ->addAction(KStandardAction::Open, QStringLiteral("file_open"), m_viewManager->tab(), &KFTabWidget::openFile);
    // a->setShortcut(QKeySequence::Open);
    a->setWhatsThis(i18n("Open an existing tex file"));

    a=actionCollection()
        ->addAction(KStandardAction::Save, QStringLiteral("file_save"), m_viewManager->tab(), &KFTabWidget::saveFile);
    a->setWhatsThis(i18n("Save the current tex file"));
    a->setShortcut(QStringLiteral("Ctrl+Alt+S"));

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

    open_remote=new QAction("打开远程文件",this);
    open_remote->setWhatsThis(i18n("打开远程文件"));
    open_remote->setIcon(QIcon::fromTheme("document-open"));
    open_remote->setShortcut(QStringLiteral("Ctrl+Alt+O"));

    connect(open_remote,&QAction::triggered,this,&KFTEXMainWindow::showList);

    insert_link =new QToolButton(this);
    QSize siz;
    siz.setWidth(40);
    siz.setHeight(40);
    insert_link->setIcon(QIcon::fromTheme("insert-link"));
    insert_link->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    insert_link->setIconSize(siz);
    insert_link->setWhatsThis(i18n("插入一个超链接"));

    insert_newpage=new QToolButton(this);
    insert_newpage->setIcon(QIcon::fromTheme("document-new"));
    insert_newpage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    insert_newpage->setIconSize(siz);
    insert_newpage->setWhatsThis(i18n("插入新的一页"));

    insert_photo=new QToolButton(this);
    insert_photo->setIcon(QIcon::fromTheme("insert-image"));
    insert_photo->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    insert_photo->setIconSize(siz);
    insert_photo->setWhatsThis(i18n("插入一张图片"));

    textbf=new QToolButton(this);
    textbf->setIcon(QIcon::fromTheme("format-text-bold"));
    textbf->setWhatsThis(i18n("加粗选中部分"));
    textbf->setShortcut(QStringLiteral("Ctrl+B"));

    textref=new QToolButton(this);
    textref->setIcon(QIcon::fromTheme("bookmark-new"));
    textref->setWhatsThis(i18n("添加文献"));

    texcite=new QToolButton(this);
    texcite->setIcon(QIcon::fromTheme("gnumeric-link-internal"));
    texcite->setWhatsThis(i18n("添加引用"));

    textit=new QToolButton(this);
    textit->setIcon(QIcon::fromTheme("format-text-italic"));
    textit->setWhatsThis(i18n("斜体选中部分"));

    insert_underline=new QToolButton(this);
    insert_underline->setIcon(QIcon::fromTheme("format-text-underline"));
    insert_underline->setWhatsThis(i18n("添加下划线"));

    insert_sdu_beamer=new QToolButton(this);
    insert_sdu_beamer->setIcon(QIcon::fromTheme("project-development-new-template"));
    insert_sdu_beamer->setWhatsThis(i18n("加入 SDU Beamer 模板"));
    connect(insert_link,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral("\\href{}{}"));
    });
    connect(insert_sdu_beamer,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral(
    "\\documentclass{beamer}\n"
    "\\usepackage{ctex, hyperref}\n"
    "\\usepackage[T1]{fontenc}\n"
    "\\usepackage{latexsym,amsmath,xcolor,multicol,booktabs,calligra}\n"
    "\\usepackage{graphicx,pstricks,listings,stackengine}\n"
    "\\author{孙更欣}\n"
    "\\title{SDU Beamer}\n"
    "\\subtitle{QT大作业模}\n"
    "\\institute{山东大学泰山学堂}\n"
    "\\date{2023年10月1日}\n"
    "\\mode<presentation>\n"
    "%\\DeclareOptionBeamer{secheader}{\\beamer@secheadertrue}\n"
    "\\ProcessOptionsBeamer\n"
    "\\useoutertheme[footline=authorinstitutetitle]{smoothbars}\n"
    "\\makeatletter\n"
    "\\newcommand{\\frameofframes}{/}\n"
    "\\newcommand{\\setframeofframes}[1]{\\renewcommand{\\frameofframes}{#1}}\n"
    "\\setbeamertemplate{footline}\n"
    "{%\n"
    "  \\begin{beamercolorbox}[colsep=1.5pt]{upper separation line foot}\n"
    "  \\end{beamercolorbox}\n"
    "  \\begin{beamercolorbox}[ht=2.5ex,dp=1.125ex,leftskip=.3cm,rightskip=.3cm plus1fil]{author in head/foot}%\n"
    "    \\leavevmode{\\usebeamerfont{author in head/foot}\\insertshortauthor}%\n"
    "    \\hfill%\n"
    "    {\\usebeamerfont{institute in head/foot}\\usebeamercolor[fg]{institute in head/foot}\\insertshortinstitute}%\n"
    "  \\end{beamercolorbox}%\n"
    "  \\begin{beamercolorbox}[ht=2.5ex,dp=1.125ex,leftskip=.3cm,rightskip=.3cm plus1fil]{title in head/foot}%\n"
    "    {\\usebeamerfont{title in head/foot}\\insertshorttitle}%\n"
    "    \\hfill%\n"
    "    {\\usebeamerfont{frame number}\\usebeamercolor[fg]{frame number}\\insertframenumber~\\frameofframes~\\inserttotalframenumber}\n"
    "  \\end{beamercolorbox}%\n"
    "  \\begin{beamercolorbox}[colsep=1.5pt]{lower separation line foot}\n"
    "  \\end{beamercolorbox}\n"
    "}\n"
    "\\makeatother\n"
    "\\useinnertheme{circles}\n"
    "%\\useoutertheme{default}\n"
    "%\\useinnertheme[shadow=true]{rounded}\n"
    "\\xdefinecolor{peaking}{rgb}{0.5,0.0,0.0}\n"
    "\\setbeamercolor{footline}{bg=peaking}\n"
    "\\setbeamercolor{frametitle}{bg=peaking,fg=white}\n"
    "\\setbeamercolor{title}{bg=peaking}\n"
    "\\setbeamerfont{frametitle}{size=\\large}\n"
    "\\setbeamertemplate{bibliography item}[text]\n"
    "\\setbeamertemplate{caption}[numbered]\n"
    "\\setbeamercolor{palette primary}{use=structure,fg=white,bg=structure.fg}\n"
    "\\setbeamercolor{palette secondary}{use=structure,fg=white,bg=structure.fg!75!black}\n"
    "\\setbeamercolor{palette tertiary}{use=structure,fg=white,bg=structure.fg!50!black}\n"
    "\\setbeamercolor{palette quaternary}{fg=white,bg=structure.fg!50!black}\n"
    "%\\setbeamercolor*{sidebar}{use=structure,bg=structure.fg}\n"
    "\\setbeamercolor{titlelike}{parent=palette primary}\n"
    "\\setbeamercolor{block title}{bg=peaking,fg=white}\n"
    "\\setbeamercolor*{block title example}{use={normal text,example text},bg=white,fg=peaking}\n"
    "\\setbeamercolor{fine separation line}{}\n"
    "\\setbeamercolor{item projected}{fg=white}\n"
    "\\setbeamercolor{palette sidebar primary}{use=normal text,fg=normal text.fg}\n"
    "\\setbeamercolor{palette sidebar quaternary}{use=structure,fg=structure.fg}\n"
    "\\setbeamercolor{palette sidebar secondary}{use=structure,fg=structure.fg}\n"
    "\\setbeamercolor{palette sidebar tertiary}{use=normal text,fg=normal text.fg}\n"
    "%\\setbeamercolor{palette sidebar quaternary}{fg=white}\n"
    "\\setbeamercolor{section in sidebar}{fg=brown}\n"
    "\\setbeamercolor{section in sidebar shaded}{fg=grey}\n"
    "\\setbeamercolor{separation line}{}\n"
    "\\setbeamercolor{sidebar}{bg=peaking}\n"
    "\\setbeamercolor{sidebar}{parent=palette primary}\n"
    "\\setbeamercolor{structure}{fg=peaking}\n"
    "\\setbeamercolor{subsection in sidebar}{fg=brown}\n"
    "\\setbeamercolor{subsection in sidebar shaded}{fg=grey}\n"
    "\\AtBeginSection[]{\n"
    "  \\begin{frame}\n"
    "    \\tableofcontents[sectionstyle=show/shaded,subsectionstyle=show/shaded/hide,subsubsectionstyle=show/shaded/hide]\n"
    "  \\end{frame}\n"
    "}\n"
    "\\AtBeginSubsection[]{\n"
    "  \\begin{frame}\n"
    "    \\tableofcontents[sectionstyle=show/shaded,subsectionstyle=show/shaded/hide,subsubsectionstyle=show/shaded/hide]\n"
    "  \\end{frame}\n"
    "}\n"
    "\\mode<all>\n"
    "% defs\n"
    "\\def\\cmd#1{\\texttt{\\color{red}\\footnotesize $\\backslash$#1}}\n"
    "\\def\\env#1{\\texttt{\\color{blue}\\footnotesize #1}}\n"
    "\\definecolor{deepblue}{rgb}{0,0,0.5}\n"
    "\\definecolor{deepred}{rgb}{0.6,0,0}\n"
    "\\definecolor{deepgreen}{rgb}{0,0.5,0}\n"
    "\\definecolor{halfgray}{gray}{0.55}\n"
    "\\lstset{\n"
    "  basicstyle=\\ttfamily\\small,\n"
    "  keywordstyle=\\bfseries\\color{deepblue},\n"
    "  emphstyle=\\ttfamily\\color{deepred},\n"
    "  stringstyle=\\color{deepgreen},\n"
    "  numbers=left,\n"
    "  numberstyle=\\small\\color{halfgray},\n"
    "  rulesepcolor=\\color{red!20!green!20!blue!20},\n"
    "  frame=shadowbox,\n"
    "}\n"
    "\\begin{document}\n"
    "\\kaishu\n"
    "\\begin{frame}\n"
    "  \\titlepage\n"
    "  \\begin{figure}[htpb]\n"
    "    \\begin{center}\n"
    "    \\end{center}\n"
    "  \\end{figure}\n"
    "\\end{frame}\n"
    "\\begin{frame}\n"
    "  \\tableofcontents[sectionstyle=show,subsectionstyle=show/shaded/hide,subsubsectionstyle=show/shaded/hide]\n"
    "\\end{frame}\n"
    "\\end{document}\n"
));
    });
    connect(insert_photo,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral("\\begin{figure}\n    centering\n   includegraphics[width=1.0\\linewidth]{cite.png}\n    caption{Enter Caption}\n    label{fig:enter-label}\n\\end{figure}"));
    });
    connect(insert_newpage,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral(""));
    });
    connect(texcite,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral("\\cite{}"));
    });
    connect(textref,&QToolButton::clicked,this,[this](){
        emit buttonClicked1(QStringLiteral("\\ref{}"));
    });
    connect(textbf,&QToolButton::clicked,this,[this](){
        emit buttonClicked2(QStringLiteral("\\textbf{"),QStringLiteral("}"));
    });
    connect(textit,&QToolButton::clicked,this,[this](){
        emit buttonClicked2(QStringLiteral("\\textit{"),QStringLiteral("}"));
    });
    connect(insert_underline,&QToolButton::clicked,this,[this](){
        emit buttonClicked2(QStringLiteral("\\underline{"),QStringLiteral("}"));
    });
    
    connect(this,&KFTEXMainWindow::buttonClicked1,m_viewManager->tab(),&KFTabWidget::instext1);
    connect(this,&KFTEXMainWindow::buttonClicked2,m_viewManager->tab(),&KFTabWidget::instext2);
}

void KFTEXMainWindow::setupMenu(){
    m_fileMenu=this->menuBar()->addMenu(i18n("&File"));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_new")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_open")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("file_save")));
    m_fileMenu->addAction(actionCollection()->action(QStringLiteral("pdf_close")));
    m_fileMenu->addAction(open_remote);
    m_fileMenu->addAction(m_fileOpenRecent);
    m_runMenu=this->menuBar()->addMenu(i18n("Run"));
    run_pdf =new QAction("run",this);
    run_pdf->setShortcut(QStringLiteral("F11"));
    run_pdf->setIcon(QIcon::fromTheme("system-run"));
    connect(run_pdf,&QAction::triggered,m_viewManager->tab(),&KFTabWidget::sendFile);
    m_runMenu->addAction(run_pdf);

    m_AboutMenu=this->menuBar()->addMenu(i18n("About"));
    m_AboutMenu->addAction(actionCollection()->action(QStringLiteral("about_app")));
    m_AboutMenu->addAction(actionCollection()->action(QStringLiteral("about_KDE")));
    toolbar->addWidget(insert_link);
    toolbar->addWidget(insert_newpage);
    toolbar->addWidget(insert_photo);
    toolbar->addWidget(textref);
    toolbar->addWidget(texcite);
    toolbar->addWidget(textbf);
    toolbar->addWidget(textit);
    toolbar->addWidget(insert_underline);
    toolbar->addWidget(insert_sdu_beamer);
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

void KFTEXMainWindow::showList(){

    if(m_listw){
        delete m_listw;
    }
    m_listw =new ListDialog(this);

    m_listw->setMinimumHeight(800);
    m_listw->setMinimumWidth(600);

    m_listw->exec();
}