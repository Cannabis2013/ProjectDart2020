#include "urlparser.h"

UrlParser::UrlParser()
{

}

QUrl UrlParser::parseUrl(const QString &baseUrl,
                        const QString &method,
                        const QString &paramterString,
                        const QString &queryString)
{
    /*
     * Template: {baseUrl}/{Method}/{urlParameter}?code={userCode}
     * Example: www.testapi.dk/api/DeleteTournament/ad4a22ee-4c5c-4911-a01f-d9578edb387c?code={{code}}
     */

    QString hostUrl = baseUrl;
    QString urlMethod = method;
    QString urlCode = queryString;

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    if(urlMethod.at(method.length() - 1 ) != '/' && paramterString != QString())
        urlMethod.append('/');
    else if(urlMethod.at(method.length() - 1 ) == '/' && paramterString == QString())
        urlMethod.remove(urlMethod.count() -1,1);

    hostUrl += urlMethod;

    if(paramterString != QString())
        hostUrl += paramterString;

    if(urlCode != QString())
        hostUrl += "?code=" + urlCode;

    return QUrl(hostUrl);
}
