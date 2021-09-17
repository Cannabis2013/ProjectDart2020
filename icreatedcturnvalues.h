#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H

#include "idcindexservice.h"
#include "idcscoresservice.h"
#include "idartsinputfinishes.h"
#include "dcturnvalues.h"
#include <dcturnvalues.h>

class ICreateDCTurnValues
{
public:
    virtual const  DCContext::DCTurnValues *createTurnValues(const IDCIndexService *indexService,
                                                             IDCScoresService *scoresService,
                                                             const IDartsInputFinishes *logisticService = nullptr) const = 0;
};
#endif // IBUILDTURNVALUES_H
