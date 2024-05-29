#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringDecoder>
#include <QObject>
#include <QMessageBox>
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
