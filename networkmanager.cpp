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
    if(slot != nullptr)
        connect(_netMng,SIGNAL(finished(QNetworkReply*)),reciever,slot);
    else
        connect(_netMng,SIGNAL(finished(QNetworkReply*)),this,SLOT(handleReply()));

    cout << "Get request called" << endl;
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,stringQuery);
    cout << fullServerUrl.toString().toStdString() << endl;
    auto reply = _netMng->get(QNetworkRequest(fullServerUrl));
    cout << "Post get request sent" << endl;
    _responseTimer.start();

    if(timeoutSlot != nullptr)
    {
        ReplyTimeout::setTimer(reply,
                               timeoutThreshold(),
                               ReplyTimeout::Abort,
                               reciever, timeoutSlot);
    }
    else
    {
        ReplyTimeout::setTimer(reply,
                               timeoutThreshold(),
                               ReplyTimeout::Abort,
                               this, SLOT(handleTimeOut()));
    }
    cout << "Method ended" << endl;
    return reply;
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
    auto reply = _netMng->post(req,data);
    _responseTimer.start();
    if(slot != nullptr)
        connect(reply,SIGNAL(finished()),reciever,slot);
    else
        connect(reply,SIGNAL(finished()),this,SLOT(handleReply()));

    ReplyTimeout::setTimer(reply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,timeoutSlot);
    return reply;
}


QNetworkReply *NetworkManager::sendDeleteRequest(const QString &method,
                                       const QString &urlParameter,
                                       const QVector<Query> stringQuery,
                                       QObject *reciever,
                                       const char* slot,
                                       const char* timeoutSlot)
{
    QUrl fullServerUrl = _parserService->parseUrl(_baseUrl,method,urlParameter,stringQuery);
    auto reply = _netMng->deleteResource(QNetworkRequest(fullServerUrl));

    _responseTimer.start();

    if(slot != nullptr)
        connect(reply,SIGNAL(finished()),reciever,slot);
    else
        connect(reply,SIGNAL(finished()),this,SLOT(handleReply()));

    connect(reply,&QNetworkReply::finished,reply,&QNetworkReply::deleteLater);

    ReplyTimeout::setTimer(reply,
                           timeoutThreshold(),
                           ReplyTimeout::Abort,
                           reciever,
                           timeoutSlot);
    return reply;
}

void NetworkManager::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);

    // TODO: Handle Ssl errors when its time for that
    for (auto err : errors) {
        cout << err.errorString().toStdString() << endl;
    }

    reply->ignoreSslErrors();
}

void NetworkManager::handleAuthRequired(QNetworkReply *reply, QAuthenticator*)
{
    cout << "Auth required" << endl;
}

void NetworkManager::handleEncrypted(QNetworkReply *reply)
{
    cout << "Encrypted called" << endl;

}

void NetworkManager::handleReply()
{
    cout << "Default reply handling" << endl;
}

void NetworkManager::handleTimeOut()
{
    cout << "Timeout occured" << endl;
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
