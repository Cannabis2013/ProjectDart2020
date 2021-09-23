#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H

#include "DCIndexSLAs/idcindexservice.h"
#include "DCScoresSLAs/idcscoresservice.h"
#include "DCFinishesSLAs/idartsinputfinishes.h"
#include "DCTurnValuesServices/dcturnvalues.h"

class ICreateDCTurnValues
{
public:
    virtual const  DCContext::DCTurnValues *createTurnValues(const IDCIndexService *indexService,
                                                             IDCScoresService *scoresService,
                                                             const IDartsInputFinishes *logisticService = nullptr) const = 0;
};
#endif // IBUILDTURNVALUES_H
