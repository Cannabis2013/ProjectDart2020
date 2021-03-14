#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <QNetworkReply>
#include <qnetworkconfiguration.h>
#include <qlist.h>
#include <QTime>
#include <QElapsedTimer>
#include <iostream>
#include <quuid.h>
// Custom includes
#include "replytimeout.h"
#include "urlparser.h"

using namespace std;

class NetworkManager : public QObject,
        private IUrlParser<IParserService*>
{
    Q_OBJECT
public:
    NetworkManager(const QString &serverHostUrl, const QString &code = QString());

    QString baseUrl() const;
    void setBaseUrl(const QString &baseUrl);

    void setUserCode(const QString &value);

    int timeoutThreshold() const;
    void setTimeoutThreshold(int timeoutThreshold);

    void setParserService(IParserService* t);
    const IParserService* parserService();

signals:
    void sendNotification(const bool &success,const QByteArray &data = QByteArray());
    void sendErrorString(const QString &err);
    void sendSslErrorStrings(const QStringList &err);

protected:

    void sendGetRequest(const QString &method,
                        const QString &urlParameter = QString(),
                        QObject* reciever = nullptr,
                        const char* slot = nullptr);
    void sendPostRequest(const QString &method,
                          const QByteArray &data,
                         const QString &urlParameters = QString(),
                         QObject *reciever = nullptr,
                         const char *slot= nullptr);
    void sendDeleteRequest(const QString &method,
                           const QString &urlParameter = QString(),
                           QObject *reciever = nullptr,
                           const char* slot = nullptr);

    int timeElapsed();
    bool errorOccured();
    QString errorString();
    const QByteArray extractData();

private slots:
    void handleSslErrors(QNetworkReply *reply,const QList<QSslError>&errors);

    virtual void handleReply();

private:


    QNetworkReply* tempReply;
    QNetworkAccessManager* _netMng = new QNetworkAccessManager();
    QString _baseUrl;
    QString _userCode;
    QElapsedTimer _responseTimer;
    int _timeoutThreshold = 3000;

    IParserService* _parserService;
};

#endif // HTTPINTERFACE_H
