#ifndef ADDTOTALSCORETODARTSINPUTSASJSON_H
#define ADDTOTALSCORETODARTSINPUTSASJSON_H

#include "DCJsonSLAs/iaddtotalscoretodartsinputsjson.h"
#include "DCInputSLAs/idcinputmodel.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddTotalScoreToDartsInputsAsJson : public IAddTotalScoreToDartsInputsJson
{
public:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    void addTotalScoreToInputs(QByteArray &json, const int &initialPoint, const IDCInputJsonKeys *inputKeys) const override;
private:
    QJsonArray toArray(const QByteArray &json) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    QVector<QUuid> createPlayerIds(const QJsonArray &arr, const IDCInputJsonKeys *inputKeys) const;
    void addTotalScoresToJsonArray(QJsonArray &arr, const QVector<QUuid> &playerIds, const int &initialPoint,
                                   const IDCInputJsonKeys *inputKeys) const;
    void addTotalScoreToPlayerJson(QJsonArray &arr, const QUuid &playerId, const int &initialPoint,
                                   const IDCInputJsonKeys *inputKeys) const;
    int calculateScore(const int &point, const int &modKeyCode) const;
};

#endif // ADDTOTALSCORETODARTSINPUTS_H
