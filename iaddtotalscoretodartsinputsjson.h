#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include "idartscontrollerpoint.h"
#include "idartscontrollerplayer.h"
#include <qvector.h>
#include <quuid.h>

namespace DartsPointControllerContext {
    template<typename TJsonFormat>
    class IAddTotalScoreToDartsInputsJson
    {
    public:
        typedef TJsonFormat JsonFormat;
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> InputModel;
        typedef QVector<const InputModel *> InputModels;
        virtual void addTotalScoreToInputs(JsonFormat &json, const int &initialPoint) const = 0;
    };
}


#endif // IADDTOTALSCORETODARTSPOINTS_H
