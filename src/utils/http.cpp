#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringDecoder>
#include <QObject>

HttpOperate::HttpOperate(){}

void HttpOperate::PostRequest(){
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::Attribute::Http2AllowedAttribute, true);
    QJsonDocument document;
    QByteArray _postData = document.toJson(QJsonDocument::Compact);
    m_Reply = m_NetworkManager->post(request,_postData);
    connect(m_Reply,&QNetworkReply::finished,this,&HttpOperate::ReplyFinshed);
}
void HttpOperate::GetRequest(){
    m_NetworkManager = std::make_shared<QNetworkAccessManager>();
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/"));
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
        // 处理返回的数据
        QByteArray _data = m_Reply->readAll();//读出数据
        auto toUtf16 = QStringDecoder(QStringDecoder::Utf8);
        QString str = toUtf16(_data);
        qInfo()<<"_data ==> "<<str;
    } else {
        // 处理错误
        qDebug()<<"error ==> "<<m_Reply->error();
    }
    m_Reply->deleteLater();
}
