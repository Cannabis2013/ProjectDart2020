#ifndef ADDDETAILSTOTOURNAMENTJSON_H
#define ADDDETAILSTOTOURNAMENTJSON_H

#include "iadddetailstotournamentjson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddDetailsToTournamentJson : public IAddDetailsToTournamentJson
{
public:
    QByteArray addPlayerNames(const QByteArray& json, const QVector<QString>& names) const override;
    QByteArray addWinnerName(const QByteArray&json, const QString& name) const override;
private:
    QJsonObject createJsonObject(const QByteArray &json) const;
    QByteArray createJson(const QJsonObject &jsonObject) const;
    QJsonArray createJsonArray(const QVector<QString> &names) const;
};


#endif // DARTSMODELSJSONSERVICE_H
