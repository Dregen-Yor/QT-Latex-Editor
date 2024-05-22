// #include "mainwindow.h"

// MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
//     tabwidget = std::make_shared<QTabWidget>();
//     setWindowTitle("KDTEX");
//     texLexer = std::make_shared<QsciLexerTeX>();
//     texLexer->setDefaultFont(QFont("Consolas", 18));
//     texLexer->setDefaultPaper(QColor("#303841"));
//     texLexer->setDefaultColor(QColor("#eceff1"));
//     tabwidget->setUsesScrollButtons(true);
//     tabwidget->setAttribute(Qt::WA_StyledBackground);
//     setCentralWidget(tabwidget.get());
//     tabwidget->setDocumentMode(true);
//     tabwidget->setAutoFillBackground(true);
//     tabwidget->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
//     createAction();
//     createMenu();
//     // editor_=std::shared_ptr<KTextEditor::Editor>(KTextEditor::Editor::instance());
//     // auto doc = editor_->createDocument(tabwidget.get());
//     // auto view = doc->createView(this);
//     editor[0] = std::make_shared<QsciScintilla>();
//     filename[0] = std::make_shared<QString>();
//     init(editor[0]);
//     tabwidget->addTab(editor[0].get(), "untitled");
//     tabwidget->setGeometry(0, 40, 1900, 1440);
//     tabwidget->setTabsClosable(true);
//     connect(tabwidget.get(), SIGNAL(currentChanged(int)), this,
//             SLOT(currentTab()));
// }

// MainWindow::~MainWindow() {}
// void MainWindow::init(std::shared_ptr<QsciScintilla> textedit) {
//     textedit->setFont(QFont("Consolas"));

//     textedit->setMarginsBackgroundColor(QColor("#303841"));
//     textedit->setMarginsForegroundColor(QColor("#b0bec5"));
//     textedit->setFrameShape(textedit->NoFrame);
//     // textedit->setMinimumSize(1900,1400);
//     // textedit->setBaseSize(1900,1400);
//     textedit->adjustSize();
//     // textedit->resize(1900,1400);
//     textedit->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,
//                             QsciScintilla::SC_CP_UTF8);  // 中文编码

//     textedit->setCaretForegroundColor(QColor(255, 128, 0));
//     textedit->setLexer(texLexer.get());  // 给QsciScintilla设置词法分析器

//     textedit->setMarginType(
//         0, QsciScintilla::NumberMargin);  // 设置编号为0的页边显示行号。
//     textedit->setMarginLineNumbers(0, true);  // 对该页边启用行号
//     textedit->setMarginWidth(0, 50);          // 设置页边宽度
// }
// void MainWindow::open() {
//     QUrl startUrl = QUrl::fromLocalFile(QDir::currentPath());
//     // QFileDialog::getOpenFileUrls(this, tr("Open File"), startUrl);
//     // std::shared_ptr<QFileDialog> dialog = std::make_shared<QFileDialog>(this);
//     // dialog->setDirectory(QDir::currentPath());
//     // dialog->open();
//     // QString fileName = dialog->selectedFiles().first();
//     // if (!fileName.isEmpty()) {
//     //     loadFile(fileName);
//     // }
// }
// bool MainWindow::save() {
//     if (currentFile.isEmpty()) {
//         return saveAs();
//     } else
//         return saveFile(currentFile);
// }
// bool MainWindow::saveAs() {
//     QFileDialog dialog(this);
//     dialog.setWindowModality(Qt::WindowModal);
//     dialog.setAcceptMode(QFileDialog::AcceptSave);
//     if (dialog.exec() != QDialog::Accepted)
//         return false;
//     QString tmp = dialog.selectedFiles().first();
//     qDebug() << tmp;
//     return saveFile(dialog.selectedFiles().first());
// }
// void MainWindow::about() {}
// void MainWindow::runpdf() {}
// void MainWindow::download() {}
// void MainWindow::upload() {}
// void MainWindow::currentTab() {
//     if (currentEditor() >= 0)
//         currentFile = *filename[currentEditor()];
//     else
//         currentFile = "";
//     qDebug() << currentFile << "\n";
// }
// void MainWindow::on_tabClose(const int x) {
//     tabwidget->removeTab(x);
// }

// void MainWindow::createAction() {
//     actionNew = std::make_shared<QAction>(tr("New"), this);
//     actionNew->setShortcut(QString("Ctrl+N"));
//     actionNew->setShortcutContext(Qt::ApplicationShortcut);
//     connect(actionNew.get(), &QAction::triggered, this, &MainWindow::newFile);

//     actionOpen = std::make_shared<QAction>(tr("Open File..."), this);
//     actionOpen->setShortcut(QString("Ctrl+O"));
//     connect(actionOpen.get(), &QAction::triggered, this, &MainWindow::open);

//     actionSave = std::make_shared<QAction>(tr("Save"), this);
//     actionSave->setShortcut(QString("Ctrl+S"));
//     connect(actionSave.get(), &QAction::triggered, this, &MainWindow::save);

//     actionRun = std::make_shared<QAction>(tr("Build"), this);
//     actionRun->setShortcut(QString("F11"));
//     connect(actionRun.get(), &QAction::triggered, this, &MainWindow::runpdf);

//     actionCopy = std::make_shared<QAction>(tr("Copy"), this);
//     actionCopy->setShortcut(QString("Ctrl+C"));

//     actionPaste = std::make_shared<QAction>(tr("Paste"), this);
//     actionPaste->setShortcut(QString("Ctrl+V"));

//     actionDownload = std::make_shared<QAction>(tr("Download from cloud"), this);
//     // actionDownload->setShortcut(QString("Ctrl+D"));
//     connect(actionDownload.get(), &QAction::triggered, this,
//             &MainWindow::download);

//     actionUpload = std::make_shared<QAction>(tr("upload to cloud"), this);
//     // actionDownload->setShortcut(QString("Ctrl+D"));
//     connect(actionUpload.get(), &QAction::triggered, this, &MainWindow::upload);

//     actionAbout = std::make_shared<QAction>(tr("About"), this);
//     connect(actionAbout.get(), &QAction::triggered, this, &MainWindow::about);
// }
// void MainWindow::createMenu() {
//     menuFile = std::shared_ptr<QMenu>(this->menuBar()->addMenu("File"));
//     menuFile->addAction(actionNew.get());
//     menuFile->addAction(actionOpen.get());
//     menuFile->addAction(actionSave.get());
//     menuFile->setMinimumWidth(160);
//     qDebug()<<"hello"<<"\n";
//     menuFile->addSeparator();
//     // std::cout<<"hello"<<"\n";
//     //-----------------//
//     menuEdit = std::shared_ptr<QMenu>(this->menuBar()->addMenu("Edit"));
//     menuEdit->addAction(actionCopy.get());
//     menuEdit->addAction(actionPaste.get());
//     menuEdit->setMinimumWidth(160);
//     menuEdit->addSeparator();
//     //-----------------//
//     menuTool = std::shared_ptr<QMenu>(this->menuBar()->addMenu("Tool"));
//     menuTool->addAction(actionRun.get());
//     menuTool->addAction(actionUpload.get());
//     menuTool->addAction(actionDownload.get());
//     menuTool->setMinimumWidth(160);
//     menuTool->addSeparator();
//     //-----------------//
//     menuHelp = std::shared_ptr<QMenu>(this->menuBar()->addMenu("Help"));
//     menuHelp->addAction(actionAbout.get());
//     menuHelp->setMinimumWidth(160);
//     menuHelp->addSeparator();
// }
// int MainWindow::newfile(const QString& fileName) {
//     editor[++cnt] = std::make_shared<QsciScintilla>();
//     filename[cnt] = std::make_shared<QString>(fileName);
//     init(editor[cnt]);
//     if (fileName.isEmpty())
//         tabwidget->addTab(editor[cnt].get(), "untitled");
//     else
//         tabwidget->addTab(editor[cnt].get(), fileName);
//     return cnt;
// }
// void MainWindow::newFile() {
//     editor[++cnt] = std::make_shared<QsciScintilla>();
//     filename[cnt] = std::make_shared<QString>();
//     init(editor[cnt]);
//     tabwidget->addTab(editor[cnt].get(), "untitled");
// }
// void MainWindow::setCurrentFile(const QString& fileName) {
//     int tmp = currentEditor();
//     *filename[tmp] = currentFile = fileName;
//     editor[tmp]->setModified(false);
//     // textedit->document()->setModified(false);
//     setWindowModified(false);

//     QString shownName = currentFile;
//     //    if (currentFile.isEmpty())
//     //        shownName = "untitled.tex";
//     setWindowFilePath(shownName);
//     tabwidget->setTabText(tmp, shownName);
// }
// bool MainWindow::boolSave() {
//     if (!editor[currentEditor()]->isModified())
//         return true;
//     const QMessageBox::StandardButton ret = QMessageBox::warning(
//         this, tr("Application"),
//         tr("The document has been modified.\n"
//            "Do you want to save your changes?"),
//         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//     switch (ret) {
//         case QMessageBox::Save:
//             return save();
//         case QMessageBox::Cancel:
//             return false;
//         default:
//             break;
//     }
//     return true;
// }
// bool MainWindow::saveFile(const QString& fileName) {
//     QFile file(fileName);
//     if (!file.open(QFile::WriteOnly | QFile::Text)) {
//         QMessageBox::warning(
//             this, tr("Application"),
//             tr("Cannot write file %1:\n%2.")
//                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
//         return false;
//     }
//     QTextStream out(&file);
//     out << editor[currentEditor()]->text();
//     setCurrentFile(fileName);
//     statusBar()->showMessage(tr("File saved"), 2000);
//     return true;
// }
// int MainWindow::currentEditor() {
//     return tabwidget->currentIndex();
// }
// void MainWindow::loadFile(const QString& fileName) {
//     QFile file(fileName);
//     if (!file.open(QFile::ReadOnly | QFile::Text)) {
//         QMessageBox::warning(
//             this, tr("Application"),
//             tr("Cannot read file %1:\n%2.")
//                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
//         return;
//     }
//     QTextStream in(&file);
//     int nowcnt = newfile(fileName);
//     tabwidget->setCurrentIndex(nowcnt);
//     editor[nowcnt]->setText(in.readAll());
//     setCurrentFile(fileName);
//     statusBar()->showMessage(tr("File loaded"), 2000);
// }
// QString MainWindow::getname(const int now) {
//     int last = 0;
//     std::string tmp = filename[now]->toStdString();
//     int len = tmp.length();
//     for (int i = 0; i < len; i++) {
//         if (tmp[i] == '/') {
//             last = i;
//         }
//     }
//     QString s = QString::fromStdString(tmp.substr(last + 1, len - last));
//     return s;
// }