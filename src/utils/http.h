#ifndef HTTP_UTILS
#define HTTP_UTILS

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QNetworkRequest>
#include <memory>
#include <QPdfDocument>
#include "../components/KFviewmanager.h"
class KFViewManager;
class HttpOperate:public QObject{
    Q_OBJECT
public:
    HttpOperate(KFViewManager* m_manager);
    void PostRequest(QByteArray data,QUrl url);
    void GetRequest(QByteArray data,QUrl url);
    QPdfDocument *doc;
private:
    std::shared_ptr<QNetworkAccessManager> m_NetworkManager;
    QNetworkReply* m_Reply;
    KFViewManager *m_manager;

public slots: 
    void ReplyFinshed();
};



#endif