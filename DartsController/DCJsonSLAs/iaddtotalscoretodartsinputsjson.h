#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include <qvector.h>
#include <quuid.h>

class IAddTotalScoreToDartsInputsJson
{
public:
    typedef QVector<const DCContext::IDCInputModel *> InputModels;
    virtual void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const = 0;
};
#endif // IADDTOTALSCORETODARTSPOINTS_H
