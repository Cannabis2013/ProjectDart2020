#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H

#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"

class ICreateDCTurnValues
{
public:
    virtual DCTurnValues turnValues(const IDCIndexController *indexService,IDCScoresService *scoresService,
                                    const IDartsInputFinishes *logisticService = nullptr) const = 0;
};
#endif // IBUILDTURNVALUES_H
