#include "KFeditviewspace.h"
#include <iostream>
class HttpOperate;
KFTabWidget::KFTabWidget(QWidget *parent,KFViewManager *manager, KTextEditor::Editor *editor):QTabWidget(parent){
    this->setTabsClosable(true);
    this->tabBar()->setTabButton(0,QTabBar::RightSide,nullptr);
    connect(this,&QTabWidget::tabCloseRequested,this,&KFTabWidget::on_tabWidget_tabCloseRequested);
    m_manager=manager;
    m_editor=editor;
    QWidget *welcomeTab = new QWidget();
    // QVBoxLayout *layout = new QVBoxLayout(welcomeTab);
    QLabel *label = new QLabel("Welcome to KFTabWidget!", welcomeTab);
    welcomeTab->setLayout(new QVBoxLayout);
    welcomeTab->layout()->addWidget(label);
    welcomeTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->addTab(welcomeTab,"Welcome");

    KTextEditor::Document *doc = m_editor->createDocument(this);
    // if(doc){
    //     createView(doc,QString("Untitled"));
    // }
}
KFTabWidget::~KFTabWidget(){
    this->close();
    delete this;
};

KTextEditor::View *KFTabWidget::createView(KTextEditor::Document *doc,QString name){
    KTextEditor::View *view=doc->createView(this,this->m_manager->mainwindow()->wrapper());
    this->addTab(view,name);
    return view;
}
QWidget *KFTabWidget::getactiveTab(){
    return this->currentWidget();
}

KTextEditor::Document *KFTabWidget::getDocumentFromView(KTextEditor::View *view) {
    return view ? view->document() : nullptr;
}
void KFTabWidget::addMath(QString txt){
    QWidget *widget=getactiveTab();
    KTextEditor::View *view=dynamic_cast<KTextEditor::View*>(widget);
    KTextEditor::Document *doc=getDocumentFromView(view);
    if(doc){
        doc->insertText(view->cursorPosition(),txt);
    }
}
void KFTabWidget::saveFile(){
    QWidget *widget=getactiveTab();
    KTextEditor::View *view=dynamic_cast<KTextEditor::View*>(widget);
    KTextEditor::Document *doc=getDocumentFromView(view);
    if(doc){
        doc->save();
    }
}
void KFTabWidget::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this->m_manager->mainwindow(), i18n("Open File"),QDir::currentPath(),QStringLiteral("Tex File(*.tex)"));
    QFileInfo fileInfo(fileName);

    if (!fileName.isEmpty()) {
        KTextEditor::Document *doc = m_editor->createDocument(this);
        if (doc) {
            QUrl fileUrl = QUrl::fromLocalFile(fileInfo.absolutePath()+"/"+fileInfo.fileName());
            qDebug()<<fileName;
            doc->openUrl(fileUrl);
            m_manager->mainwindow()->addRecentOpenedFile(fileUrl);
            createView(doc,fileInfo.fileName());
        }
    }
}
void KFTabWidget::newFile() {
    // 打开文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this->m_manager->mainwindow(), tr("New File"), QDir::currentPath(),QStringLiteral("Tex File(*.tex)"));

    if (!fileName.isEmpty()) {
        // 创建一个新的文档
        KTextEditor::Document *doc = m_editor->createDocument(this);

        if (doc) {
            // 保存文档为新文件
            QUrl fileUrl = QUrl::fromLocalFile(fileName);
            doc->saveAs(fileUrl);
            m_manager->mainwindow()->addRecentOpenedFile(fileUrl);
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
void KFTabWidget::on_tabWidget_tabCloseRequested(int index){
    this->removeTab(index);
}
void KFTabWidget::openRecent(QUrl url){
    KTextEditor::Document *doc = m_editor->createDocument(this);
    if(doc){
        doc->openUrl(url);
        createView(doc,url.fileName());
    }
}
void KFTabWidget::sendFile(){
    QWidget *widget=getactiveTab();
    if(!(qobject_cast<KTextEditor::View*>(widget))){
        LOG(WARNING)<<"请选择一个编辑器视图";
        return;
    }
    KTextEditor::View *v=dynamic_cast<KTextEditor::View*>(widget);
    KTextEditor::Document *doc = getDocumentFromView(v);
    QUrl fileUrl = doc->url();
    QFile file=QFile(fileUrl.toLocalFile());
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Failed to open file:" << fileUrl;
        return;
    }
    QByteArray filecontent= file.readAll();
    file.close();
    QJsonObject json ;
    json["filename"]=QFileInfo(file).baseName();
    json["filedata"]=QString(filecontent);
    QByteArray jsonData=QJsonDocument(json).toJson();
    HttpOperate *request =new HttpOperate(m_manager);
    request->PostRequest(jsonData,QUrl("http://127.0.0.1:1503/compile"));

}
void Insert(QString){

}
void KFTabWidget::instext2(QString str1,QString str2){
    QWidget *widget=getactiveTab();
    if(!(qobject_cast<KTextEditor::View*>(widget))){
        LOG(WARNING)<<"请选择一个编辑器视图";
        return;
    }
    KTextEditor::View *v=dynamic_cast<KTextEditor::View*>(widget);
    QString mid=v->selectionText();
    v->removeSelectionText();
    v->insertText(str1+mid+str2);
    
}

void KFTabWidget::instext1(QString str1){
    QWidget *widget=getactiveTab();
    if(!(qobject_cast<KTextEditor::View*>(widget))){
        LOG(WARNING)<<"请选择一个编辑器视图";
        return;
    }
    KTextEditor::View *v=dynamic_cast<KTextEditor::View*>(widget);
    v->insertText(str1);
}