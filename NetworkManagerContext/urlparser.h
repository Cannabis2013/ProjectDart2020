#ifndef MYPARSER_H
#define MYPARSER_H

#define SINGLELINE_QUERY_PARAMETERS

#include "iurlparser.h"
#include <qurl.h>
#include <qstring.h>

#include <iostream>

using namespace std;

class UrlParser : public IParserService<QUrl,QString,QString, QVector<QPair<QString,QString>>>
{
public:
    UrlParser();

    QUrl parseUrl(const QString &baseUrl,
                  const QString &method,
                  const QString &paramterString,
                  const QVector<QPair<QString, QString> > &queryElements) override;

private:
    QString createStringQuery(const QVector<QPair<QString,QString>>& queries);
};
#endif // MYPARSER_H
