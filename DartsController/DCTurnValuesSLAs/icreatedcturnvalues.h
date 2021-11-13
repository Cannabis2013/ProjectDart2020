#ifndef ICREATEDCTURNVALUES_H
#define ICREATEDCTURNVALUES_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class ICreateDCTurnValues
{
public:
    virtual DCTurnValues turnValues(IDartsIndex *index, IDCScoreModels *scoresService,
                                    const IDartsInputFinishes *logisticService = nullptr) const = 0;
};
#endif // IBUILDTURNVALUES_H
