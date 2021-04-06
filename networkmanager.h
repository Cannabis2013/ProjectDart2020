#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qnetworkconfiguration.h>
#include <qlist.h>
#include <QTime>
#include <QElapsedTimer>
#include <iostream>
#include <quuid.h>
#include <qauthenticator.h>
// Custom includes
#define SINGLELINE_QUERY_PARAMETERS
#include "replytimeout.h"
#include "iurlparser.h"

using namespace std;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    typedef QPair<QString,QString> Query;
    typedef IParserService<QUrl,QString, QString, QVector<Query>> Iparser;
    enum ConnectionOptions {
        ShowSslErrors = 0x1,
        IgnoreSSlErrors = 0x2
    };
    NetworkManager(const QString &serverHostUrl);

    QString baseUrl() const;

    void setUserCode(const QString &value);

    int timeoutThreshold() const;
    void setTimeoutThreshold(int timeoutThreshold);

    void setParserService(Iparser* t);
    const Iparser *parserService();


    QNetworkReply* sendGetRequest(const QString &method,
                        const QString &urlParameter,
                        const QVector<Query> stringQuery,
                        QObject* reciever = nullptr,
                        const char* slot = nullptr,
                        const char *timeoutSlot = nullptr);
    QNetworkReply* sendPostRequest(const QString &method,
                         const QByteArray &data,
                         const QString &urlParameters,
                         const QVector<Query> stringQuery,
                         QObject *reciever = nullptr,
                         const char *slot= nullptr,
                         const char *timeoutSlot = nullptr);
    QNetworkReply* sendDeleteRequest(const QString &method,
                           const QString &urlParameter,
                           const QVector<Query> stringQuery,
                           QObject *reciever = nullptr,
                           const char* slot = nullptr,
                           const char *timeoutSlot = nullptr);
    int timeElapsed();
    ConnectionOptions connectionOptions() const;
    void setConnectionOptions(const ConnectionOptions &options);

    QNetworkReply *reply();

signals:
    void sendNotification(const bool &success,const QByteArray &data = QByteArray());
    void sendErrorString(const QString &err);
    void sendSslErrorStrings(const QStringList &err);
    void timeOutOccured(const QString& msg);

private slots:
    void handleSslErrors(QNetworkReply *reply,const QList<QSslError>&errors);
    void handleAuthRequired(QNetworkReply *reply, QAuthenticator *);
    void handleEncrypted(QNetworkReply *reply);
    virtual void handleReply();
    virtual void handleTimeOut();

private:

    QNetworkAccessManager* _netMng = new QNetworkAccessManager();
    QNetworkReply* _tempReply;
    const QString _baseUrl;
    QElapsedTimer _responseTimer;
    int _timeoutThreshold = 3000;
    ConnectionOptions _options;
    Iparser* _parserService;
};

#endif // HTTPINTERFACE_H
