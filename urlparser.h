#ifndef MYPARSER_H
#define MYPARSER_H

#define SINGLELINE_QUERY_PARAMETERS

#include "iurlparser.h"
#include <qurl.h>
#include <qstring.h>

class UrlParser : public IParserService<QUrl,QString,QString, QVector<QPair<QString,QString>>>
{
public:
    UrlParser();

    QUrl parseUrl(const QString &baseUrl,
                  const QString &method,
                  const QString &paramterString,
                  const QVector<QPair<QString, QString> > &queryElements) override;

private:
    QString assembleStringQuery(const QVector<QPair<QString,QString>>& queries)
    {
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
};
#endif // MYPARSER_H
