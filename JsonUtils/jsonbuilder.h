#ifndef JSONBUILDER_H
#define JSONBUILDER_H
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DartsModelsContext/InputsDbSLAs/idartsinputjsonbuilder.h"
#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
class JsonBuilder
{
public:
    JsonBuilder(IDartsJsonBuilder *dartsJson, IModel<QUuid> *darts,
                IDartsInputJsonBuilder *inputJson, const QVector<IModel<QUuid>*> &inputs)
    {
        add(dartsJson->tournamentJsonObject(darts),"index");
        add(dartsJson->assignedPlayersJson(darts),"players");
        add(dartsJson->winnerDetailsJson(darts),"winnerDetails");
        add(inputJson->jsonArray(inputs),"inputs");
    }
    QByteArray get()
    {
        return toByteArray();
    }
private:
    void add(const QJsonObject &obj, const QString &key)
    {
        _obj[key] = obj;
    }
    void add(const QJsonArray &arr, const QString &key)
    {
        _obj[key] = arr;
    }
    QByteArray toByteArray() const
    {
        return QJsonDocument(_obj).toJson();
    }
    QJsonObject _obj;
};

#endif // JSONBUILDER_H
