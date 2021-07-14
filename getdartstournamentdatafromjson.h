#ifndef GETDARTSTOURNAMENTDATAFROMJSON_H
#define GETDARTSTOURNAMENTDATAFROMJSON_H

#include "igetdartstournamentdatafromjson.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class GetDartsTournamentDataFromjson : public IGetDartsTournamentDataFromJson
{
public:
    virtual Id tournamentIdFromJson(const Json &json) const override;
    virtual Id winnerIdFromJson(const Json &json) const override;
private:
    QJsonObject createJsonObject(const QByteArray &json) const;
};

#endif // GETDARTSTOURNAMENTDATAFROMJSON_H
