#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include <qvector.h>
#include <quuid.h>

#include "DartsController/DCInputServices/dcinput.h"
class IAddTotalScoreToDartsInputsJson
{
public:
    typedef QVector<const DCInput> InputModels;
    virtual void addRemainingScoreToInputs(QByteArray &json, const int &initialPoint) const = 0;
};
#endif // IADDTOTALSCORETODARTSPOINTS_H
