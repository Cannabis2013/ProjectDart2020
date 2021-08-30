#ifndef ICREATEDPCTURNVALUES_H
#define ICREATEDPCTURNVALUES_H

#include "idartspointindexservice.h"
#include "idcscoresservice.h"
#include "idartsinputsuggestion.h"
#include "dartspointturnvalues.h"
#include "idcplayer.h"
#include "idpcmodel.h"
#include "idpcindexes.h"
#include "icreatedcturnvalues.h"

namespace DPCContext {
    class ICreateDPCTurnValues : public ICreateDCTurnValues<const DartsPointTurnValues*,
                                                            const IDartsPointIndexService*,
                                                            IDCScoresService*,
                                                            const IDartsInputSuggestion*>
    {
    public:
        virtual const  DartsPointTurnValues *createTurnValues(const IDartsPointIndexService *indexService,
                                                              IDCScoresService *scoresService,
                                                              const IDartsInputSuggestion *logisticService = nullptr) const = 0;
    };
}
#endif // IBUILDTURNVALUES_H
