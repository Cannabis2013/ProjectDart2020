#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include "idpcmodel.h"
#include <qvector.h>
#include <quuid.h>

namespace DPCContext {
    class IAddTotalScoreToDartsInputsJson
    {
    public:
        typedef QVector<const IDPCModel *> InputModels;
        virtual void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const = 0;
    };
}


#endif // IADDTOTALSCORETODARTSPOINTS_H
