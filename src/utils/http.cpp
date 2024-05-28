#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringDecoder>
#include <QObject>
// #include <glog/logging.h>

HttpOperate::HttpOperate(KFViewManager* manager){
    this->m_manager=manager;
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
void HttpOperate::GetRequest(QByteArray data,QUrl url){
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::Attribute::Http2AllowedAttribute, true);
    QJsonDocument document;
    QByteArray _postData = document.toJson(QJsonDocument::Compact);
    m_Reply = m_NetworkManager->get(request,_postData);
    connect(m_Reply,&QNetworkReply::finished,this,&HttpOperate::ReplyFinshed);
}
void HttpOperate::ReplyFinshed()
{
    if (m_Reply->error() == QNetworkReply::NoError)
    {
        doc=new QPdfDocument(m_manager);
        doc->load(m_Reply);
        m_manager->showPdf(doc);
        // QByteArray _data = m_Reply->readAll();//读出数据
        
        
    } else {
        // 处理错误
        qDebug()<<"error ==> "<<m_Reply->error();
    }
    m_Reply->deleteLater();
    delete this;
}
