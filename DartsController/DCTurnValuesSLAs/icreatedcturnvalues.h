#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"

class ICreateDCTurnValues
{
public:
    virtual const  DCContext::DCTurnValues *turnValues(const IDCIndexService *indexService,
                                                             IDCScoresService *scoresService,
                                                             const IDartsInputFinishes *logisticService = nullptr) const = 0;
};
#endif // IBUILDTURNVALUES_H
