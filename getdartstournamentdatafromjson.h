#ifndef GETDARTSTOURNAMENTDATAFROMJSON_H
#define GETDARTSTOURNAMENTDATAFROMJSON_H

#include "igetdartstournamentdatafromjson.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class GetDartsTournamentDataFromjson : public IGetDartsTournamentDataFromJson
{
public:
    virtual int numeric(const Json &json, const String &key) const override;
    virtual QVector<Numeric> numerics(const Json &json, const String &key) const override;
    virtual Id id(const Json &json, const String &key) const override;
private:
    QJsonObject createJsonObject(const QByteArray &json) const;
    QVector<Numeric> createNumericsFromJsonArray(const QJsonArray &arr) const;
};

#endif // GETDARTSTOURNAMENTDATAFROMJSON_H
