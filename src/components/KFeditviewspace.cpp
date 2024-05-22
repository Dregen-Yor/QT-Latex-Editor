#include "KFeditviewspace.h"

KFTabWidget::KFTabWidget(QWidget *parent,KFViewManager *manager, KTextEditor::Editor *editor):QTabWidget(parent){
    m_manager=std::shared_ptr<KFViewManager>(manager);
    m_editor=editor;
    QWidget *welcomeTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(welcomeTab);
    QLabel *label = new QLabel("Welcome to KFTabWidget!", welcomeTab);
    layout->addWidget(label);
    this->addTab(welcomeTab,"Welcome");
    // setObjectName(QString::fromLatin1(name));
}
KFTabWidget::~KFTabWidget() =default;

KTextEditor::View *KFTabWidget::createView(KTextEditor::Document *doc,QString name){
    KTextEditor::View *view=doc->createView(this);
    this->addTab(view,name);
    return view;
}
KTextEditor::View *KFTabWidget::getactiveTab(){
    return dynamic_cast<KTextEditor::View*>(this->currentWidget());
}
KTextEditor::Document *KFTabWidget::getDocumentFromView(KTextEditor::View *view) {
    return view ? view->document() : nullptr;
}
void KFTabWidget::addMath(QString txt){
    KTextEditor::View *view=getactiveTab();
    KTextEditor::Document *doc=getDocumentFromView(view);
    if(doc){
        doc->insertText(view->cursorPosition(),txt);
    }
}
void KFTabWidget::saveFile(){
    KTextEditor::View *view=getactiveTab();
    KTextEditor::Document *doc=getDocumentFromView(view);
    if(doc){
        doc->save();
    }
}
void KFTabWidget::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::currentPath());
    QFileInfo fileInfo(fileName);
    if (!fileName.isEmpty()) {
        KTextEditor::Document *doc = m_editor->createDocument(this);
        if (doc) {
            QUrl fileUrl = QUrl::fromLocalFile(fileInfo.absolutePath());
            doc->openUrl(fileUrl);
            createView(doc,fileInfo.fileName());
        }
    }
}
void KFTabWidget::newFile() {
    // 打开文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("New File"), QDir::currentPath());

    if (!fileName.isEmpty()) {
        // 创建一个新的文档
        KTextEditor::Document *doc = m_editor->createDocument(this);

        if (doc) {
            // 保存文档为新文件
            QUrl fileUrl = QUrl::fromLocalFile(fileName);
            doc->saveAs(fileUrl);

            // 创建一个新的视图
            createView(doc, QFileInfo(fileName).fileName());
        }
    }
}
void KFTabWidget::tabChanged(){
    // KTextEditor::View *view=getactiveTab();
    // KTextEditor::Document *doc=getDocumentFromView(view);
    // if(doc){
    //     m_manager->setDocument(doc);
    // }
}