#include "networkmanager.h"

NetworkManager::NetworkManager(const QString &serverHostUrl):
    _baseUrl(serverHostUrl)
{
    _netMng = new QNetworkAccessManager();

    connect(_netMng,&QNetworkAccessManager::sslErrors,
            this,&NetworkManager::handleSslErrors);
    connect(_netMng,&QNetworkAccessManager::authenticationRequired,
            this,&NetworkManager::handleAuthRequired);
    connect(_netMng,&QNetworkAccessManager::encrypted,
            this,&NetworkManager::handleEncrypted);
}

QNetworkReply *NetworkManager::sendGetRequest(const QString &method,
                                              const QString &urlParameter,
                                              const QVector<Query> stringQuery,
                                              QObject *reciever,
                                              const char *slot,
                                              const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,stringQuery);
    _tempReply = _netMng->get(QNetworkRequest(fullServerUrl));
    if(slot != nullptr)
        connect(_tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(_tempReply,SIGNAL(finished()),this,SLOT(handleReply()));

    _responseTimer.start();

    if(timeoutSlot != nullptr)
    {
        ReplyTimeout::setTimer(_tempReply,
                               timeoutThreshold(),
                               ReplyTimeout::Abort,
                               reciever, timeoutSlot);
    }
    else
    {
        ReplyTimeout::setTimer(_tempReply,
                               timeoutThreshold(),
                               ReplyTimeout::Abort,
                               this, SLOT(handleTimeOut()));
    }
    return _tempReply;
}

QNetworkReply *NetworkManager::sendPostRequest(const QString &method,
                                     const QByteArray &data,
                                     const QString &urlParameter,
                                     const QVector<Query> stringQuery,
                                     QObject* reciever,
                                     const char* slot,
                                     const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,stringQuery);
    QNetworkRequest req(fullServerUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    _tempReply = _netMng->post(req,data);
    _responseTimer.start();
    if(slot != nullptr)
        connect(_tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(_tempReply,SIGNAL(finished()),this,SLOT(handleReply()));

    ReplyTimeout::setTimer(_tempReply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,timeoutSlot);
    return _tempReply;
}


QNetworkReply *NetworkManager::sendDeleteRequest(const QString &method,
                                       const QString &urlParameter,
                                       const QVector<Query> stringQuery,
                                       QObject *reciever,
                                       const char* slot,
                                       const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,stringQuery);
    _tempReply = _netMng->deleteResource(QNetworkRequest(fullServerUrl));

    _responseTimer.start();

    if(slot != nullptr)
        connect(_tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(_tempReply,SIGNAL(finished()),this,SLOT(handleReply()));

    connect(_tempReply,&QNetworkReply::finished,_tempReply,&QNetworkReply::deleteLater);

    ReplyTimeout::setTimer(_tempReply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,
                           timeoutSlot);
    return _tempReply;
}

void NetworkManager::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    reply->ignoreSslErrors();
}

void NetworkManager::handleAuthRequired(QNetworkReply *reply, QAuthenticator*)
{
}

void NetworkManager::handleEncrypted(QNetworkReply *reply)
{
}

void NetworkManager::handleReply()
{
}

void NetworkManager::handleTimeOut()
{
    emit timeOutOccured("Timeout occured");
}

QNetworkReply *NetworkManager::reply()
{
    return _tempReply;
}

NetworkManager::ConnectionOptions NetworkManager::connectionOptions() const
{
    return _options;
}

void NetworkManager::setConnectionOptions(const ConnectionOptions &options)
{
    _options = options;
}

int NetworkManager::timeElapsed()
{
    return _responseTimer.elapsed();
}

QString NetworkManager::baseUrl() const
{
    return _baseUrl;
}


void NetworkManager::setParserService(Iparser *t)
{
    _parserService = t;
}

const Iparser *NetworkManager::parserService()
{
    return _parserService;
}

int NetworkManager::timeoutThreshold() const
{
    return _timeoutThreshold;
}

void NetworkManager::setTimeoutThreshold(int timeoutThreshold)
{
    _timeoutThreshold = timeoutThreshold;
}
