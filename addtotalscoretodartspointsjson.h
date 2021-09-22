#ifndef ADDTOTALSCORETODARTSPOINTSJSON_H
#define ADDTOTALSCORETODARTSPOINTSJSON_H

#include "iaddtotalscoretodartsinputsjson.h"
#include "DCInputsSLA/idcinputmodel.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddTotalScoreToDartsPointsJson : public IAddTotalScoreToDartsInputsJson
{
public:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const override;
private:
    QJsonArray toArray(const QByteArray &json) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    QVector<QUuid> createPlayerIds(const QJsonArray &arr) const;
    void addTotalScoresToJsonArray(QJsonArray &arr, const QVector<QUuid> &playerIds, const int &initialPoint) const;
    void addTotalScoreToPlayerJson(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const;
    int calculateScore(const int &point, const int &modKeyCode) const;
};

#endif // ADDTOTALSCORETODARTSINPUTS_H
