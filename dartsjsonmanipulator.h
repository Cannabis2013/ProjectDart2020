#ifndef DARTSJSONMANIPULATOR_H
#define DARTSJSONMANIPULATOR_H

#include "idartsjsonmanipulator.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsJsonManipulator :
        public IDartsJsonManipulator
{
public:
    QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray& json, const QVector<QString>& names) const override;
    QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&json, const QString& name) const override;
private:
    QJsonObject createJsonObject(const QByteArray &json) const;
    QByteArray createJson(const QJsonObject &jsonObject) const;
    QJsonArray createJsonArray(const QVector<QString> &names) const;
};


#endif // DARTSMODELSJSONSERVICE_H
