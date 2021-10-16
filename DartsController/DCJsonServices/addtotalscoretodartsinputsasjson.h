#ifndef ADDTOTALSCORETODARTSINPUTSASJSON_H
#define ADDTOTALSCORETODARTSINPUTSASJSON_H

#include "DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class   AddTotalScoreToDartsInputsAsJson : public IAddTotalScoreToDartsInputsJson
{
public:
    void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const override;
private:
    QJsonArray toArray(const QByteArray &json) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    QVector<QUuid> createPlayerIds(const QJsonArray &arr) const;
    void addTotalScoresToJsonArray(QJsonArray &arr, const QVector<QUuid> &playerIds, const int &initialPoint) const;
    void addTotalScoreToPlayerJson(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const;
};

#endif // ADDTOTALSCORETODARTSINPUTS_H
