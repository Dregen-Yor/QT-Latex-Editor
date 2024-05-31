#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringDecoder>
#include <QObject>
#include <iostream>
#include <fstream>
#include <QMessageBox>
// #include <glog/logging.h>

HttpOperate::HttpOperate(KFViewManager* manager){
    this->m_manager=manager;
}
HttpOperate::HttpOperate(ListDialog *d){
    dia=d;
}
HttpOperate::~HttpOperate(){

}
void HttpOperate::PostRequest(QByteArray data,QUrl url){
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::Attribute::Http2AllowedAttribute, true);
    m_Reply = m_NetworkManager->post(request,data);
    connect(m_Reply,&QNetworkReply::finished,this,&HttpOperate::ReplyFinshed);
}

void HttpOperate::GetAll(){
    QUrl url("http://127.0.0.1:1503/queryall");
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::Attribute::Http2AllowedAttribute, true);
    m_Reply = m_NetworkManager->get(request);
    connect(m_Reply,&QNetworkReply::finished,this,&HttpOperate::getAllfinished);
}

void HttpOperate::getContent(QByteArray name){
    QUrl url("http://127.0.0.1:1503/query");
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::Attribute::Http2AllowedAttribute, true);
    m_Reply = m_NetworkManager->get(request,name);
    connect(m_Reply,&QNetworkReply::finished,this,&HttpOperate::queryFinished);
}

void HttpOperate::ReplyFinshed(){
    if (m_Reply->error() == QNetworkReply::NoError)
    {
        doc=new QPdfDocument(m_manager);
        doc->load(m_Reply);
        m_manager->showPdf(doc);
        
    } else {
        if(m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==400){
            QMessageBox::warning(m_manager,QStringLiteral("错误"),QStringLiteral("编译错误,请检查你的语法"));
        }
        else{
            QMessageBox::warning(m_manager,QStringLiteral("错误"),QStringLiteral("服务器错误"));
        }
    }
    m_Reply->deleteLater();
    delete this;
}

void HttpOperate::getAllfinished(){
    if (m_Reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = m_Reply->readAll();
        
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QVariantList list = obj.value("allfile").toArray().toVariantList();
        for(auto i:list){
            dia->m_list.append(i.toString());
            dia->listWidget->addItem(i.toString());
        }
    }else{
        QMessageBox::warning(m_manager,QStringLiteral("错误"),QStringLiteral("服务器错误"));
    }
}
void HttpOperate::queryFinished(){
    if (m_Reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = m_Reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        content = doc.object().value("content").toString();
        QString filepath=QFileDialog::getSaveFileName(dia,QStringLiteral("保存文件"),QDir::currentPath(),QStringLiteral("Tex File(*.tex)"));
        std::ofstream outFile(filepath.toStdString(),std::ios::trunc);
        outFile<<content.toStdString();
        outFile.close();
        
    }else{
        QMessageBox::warning(m_manager,QStringLiteral("错误"),QStringLiteral("服务器错误"));
    }
}