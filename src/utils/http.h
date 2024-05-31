#ifndef HTTP_UTILS
#define HTTP_UTILS

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QNetworkRequest>
#include <memory>
#include <QList>
#include <QPdfDocument>
#include <QJsonArray>
#include "../components/KFviewmanager.h"
#include "../components/listdialog.hpp"
#include <QVariant>
class KFViewManager;
class HttpOperate;
class ListDialog;
class HttpOperate:public QObject{
    Q_OBJECT
public:
    HttpOperate(KFViewManager* m_manager);
    HttpOperate(ListDialog *d);
    ~HttpOperate();
    void PostRequest(QByteArray data,QUrl url);
    void GetAll();
    void getContent(QByteArray name);
    QString content;
    QPdfDocument *doc;
private:
    std::shared_ptr<QNetworkAccessManager> m_NetworkManager;
    QNetworkReply* m_Reply;
    KFViewManager *m_manager;
    ListDialog *dia;

public slots: 
    void ReplyFinshed();
    void getAllfinished();
    void queryFinished();
};


#endif