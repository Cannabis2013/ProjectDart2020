#include "urlparser.h"

UrlParser::UrlParser()
{

}

QUrl UrlParser::parseUrl(const QString &baseUrl,
                        const QString &method,
                        const QString &paramterString,
                        const QVector<QPair<QString,QString>> &queryElements)
{
    /*
     * Template: {baseUrl}/{Method}/{urlParameter}?code={userCode}
     * Example: www.testapi.dk/api/DeleteTournament/ad4a22ee-4c5c-4911-a01f-d9578edb387c?code={{code}}
     */
    QString hostUrl = baseUrl;
    QString urlMethod = method;
    auto stringQuery = assembleStringQuery(queryElements);

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    if(urlMethod != QString())
    {
        if(urlMethod.at(method.length() - 1 ) != '/' && paramterString != QString())
            urlMethod.append('/');
        else if(urlMethod.at(method.length() - 1 ) == '/' && paramterString == QString())
            urlMethod.remove(urlMethod.count() -1,1);
    }

    hostUrl += urlMethod;

    if(paramterString != QString())
        hostUrl += paramterString;

    if(stringQuery != QString())
        hostUrl += stringQuery;

    return QUrl(hostUrl);
}

QString UrlParser::assembleStringQuery(const QVector<QPair<QString, QString> > &queries)
{
    if(queries.isEmpty())
        return QString();
    auto queryList = queries;
    auto lastQuery = queryList.takeLast();

    QString result = "?";
    for (auto i = queryList.constBegin(); i != queryList.constEnd(); ++i) {
        auto query = *i;
        result += query.first + "=" + query.second + "&";
    }
    result += lastQuery.first + "=" + lastQuery.second;
    return result;
}
