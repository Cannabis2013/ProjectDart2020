#include "networkmanager.h"

NetworkManager::NetworkManager(const QString &serverHostUrl, const QString &code):
    _baseUrl(serverHostUrl),_userCode(code)
{
    _netMng = new QNetworkAccessManager();

    connect(_netMng,&QNetworkAccessManager::sslErrors,this,&NetworkManager::handleSslErrors);
}

void NetworkManager::sendGetRequest(const QString &method,
                                    const QString &urlParameter,
                                    QObject *reciever,
                                    const char *slot,
                                    const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,_userCode);

    tempReply = _netMng->get(QNetworkRequest(fullServerUrl));
    auto req = QNetworkRequest();


    _responseTimer.start();

    if(slot != nullptr)
        connect(tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(tempReply,SIGNAL(finished()),this,SLOT(handleReply()));

    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever, timeoutSlot);
}

void NetworkManager::sendPostRequest(const QString &method,
                                     const QByteArray &data,
                                     const QString &urlParameter,
                                     QObject* reciever,
                                     const char* slot,
                                     const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,_userCode);
    QNetworkRequest req(fullServerUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    tempReply = _netMng->post(req,data);
    _responseTimer.start();
    if(slot != nullptr)
        connect(tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(tempReply,SIGNAL(finished()),this,SLOT(handleReply()));
    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,timeoutSlot);
}


void NetworkManager::sendDeleteRequest(const QString &method,
                                       const QString &urlParameter,
                                       QObject *reciever,
                                       const char* slot,
                                       const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,_userCode);
    tempReply = _netMng->deleteResource(QNetworkRequest(fullServerUrl));

    _responseTimer.start();

    if(slot != nullptr)
        connect(tempReply,SIGNAL(finished()),reciever,slot);
    else
        connect(tempReply,SIGNAL(finished()),this,SLOT(handleReply()));

    connect(tempReply,&QNetworkReply::finished,tempReply,&QNetworkReply::deleteLater);

    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,
                           timeoutSlot);
}

void NetworkManager::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    // TODO: Handle Ssl errors when its time for that
}

void NetworkManager::handleReply()
{
}

void NetworkManager::setBaseUrl(const QString &baseUrl)
{
    _baseUrl = baseUrl;
}

int NetworkManager::timeElapsed()
{
    return _responseTimer.elapsed();
}

bool NetworkManager::errorOccured()
{
    return tempReply->error();
}

QString NetworkManager::errorString()
{
    return tempReply->errorString();
}

const QByteArray NetworkManager::extractData()
{
    return tempReply->readAll();
}

void NetworkManager::setUserCode(const QString &value)
{
    _userCode = value;
}

QString NetworkManager::baseUrl() const
{
    return _baseUrl;
}


void NetworkManager::setParserService(IParserService<QUrl, QString> *t)
{
    _parserService = t;
}

const IParserService<QUrl, QString> *NetworkManager::parserService()
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
