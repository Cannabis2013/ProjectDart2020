#ifndef ADDTOTALSCORETODARTSINPUTS_H
#define ADDTOTALSCORETODARTSINPUTS_H

#include "iaddtotalscoretodartsinputsjson.h"
#include "idartscontrollerpoint.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsPointControllerContext {
    class AddTotalScoreToDartsInputsJson : public IAddTotalScoreToDartsInputsJson<QByteArray>
    {
    public:
        void addTotalScoreToInputs(JsonFormat &json, const int &initialPoint) const override;
    private:
        QJsonArray createArray(const QByteArray &json) const;
        QVector<QUuid> buildListOfPlayerIds(const QJsonArray &arr) const;
        void addTotalScoresToJsonArray(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const;
        JsonFormat createJsonByArray(const QJsonArray &arr) const;
    };
}

#endif // ADDTOTALSCORETODARTSINPUTS_H
