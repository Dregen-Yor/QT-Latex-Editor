#ifndef HTTP_UTILS
#define HTTP_UTILS

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QNetworkRequest>
#include <memory>
class HttpOperate:public QObject{
    Q_OBJECT
public:
    HttpOperate();
    void PostRequest(QByteArray data,QUrl url);
    void GetRequest(QByteArray data,QUrl url);
private:
    std::shared_ptr<QNetworkAccessManager> m_NetworkManager;
    QNetworkReply* m_Reply;
public slots: 
    void ReplyFinshed();
};



#endif