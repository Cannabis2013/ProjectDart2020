#ifndef IADDTOTALSCORETODARTSINPUTSJSON_H
#define IADDTOTALSCORETODARTSINPUTSJSON_H

#include "idcmodel.h"
#include <qvector.h>
#include <quuid.h>

class IAddTotalScoreToDartsInputsJson
{
public:
    typedef QVector<const DCContext::IDCModel *> InputModels;
    virtual void addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const = 0;
};
#endif // IADDTOTALSCORETODARTSPOINTS_H
