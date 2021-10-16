#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include "DartsController/DCInputSLAs/idcinput.h"
#include <qvector.h>
#include <quuid.h>

class IAddTotalScoreToDartsInputsJson
{
public:
    typedef QVector<const IDCInput *> InputModels;
    virtual void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const = 0;
};
#endif // IADDTOTALSCORETODARTSPOINTS_H
