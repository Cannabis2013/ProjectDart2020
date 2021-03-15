#ifndef MYPARSER_H
#define MYPARSER_H

#define SINGLELINE_QUERY_PARAMETERS

#include "iurlparser.h"
#include <qurl.h>
#include <qstring.h>

class UrlParser : public IParserService<QUrl,QString>
{
public:
    UrlParser();

    QUrl parseUrl(const QString &baseUrl, const QString &method, const QString &paramterString, const QString &queryString);
};
#endif // MYPARSER_H
