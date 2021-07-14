#ifndef ADDTOTALSCORETODARTSPOINTSJSON_H
#define ADDTOTALSCORETODARTSPOINTSJSON_H

#include "iaddtotalscoretodartsinputsjson.h"
#include "idartscontrollerpoint.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsPointControllerContext {
    class AddTotalScoreToDartsPointsJson : public IAddTotalScoreToDartsInputsJson<QByteArray>
    {
    public:
        enum PointKeyCodes{
            SingleModifer = 0x2A,
            DoubleModifier = 0x2B,
            TrippleModifier = 0x2C,
            BullModifier,
            BullsEyeModifier
        };
        void addTotalScoreToInputs(JsonFormat &json, const int &initialPoint) const override;
    private:
        QJsonArray createArray(const QByteArray &json) const;
        QVector<QUuid> buildListOfPlayerIds(const QJsonArray &arr) const;
        void addTotalScoresToJsonArray(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const;
        JsonFormat createJsonByArray(const QJsonArray &arr) const;
        int calculateScore(const int &point, const int &modKeyCode) const;
    };
}

#endif // ADDTOTALSCORETODARTSINPUTS_H
