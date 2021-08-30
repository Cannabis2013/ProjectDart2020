#ifndef ICREATEDSCTURNVALUES_H
#define ICREATEDSCTURNVALUES_H

#include "icreatedcturnvalues.h"
#include "dartsscoreturnvalues.h"
#include "idsindexservice.h"
#include "idcwinnerservice.h"
#include "idscmodel.h"
#include "idartsinputsuggestion.h"
#include "idscindexes.h"
#include "idcplayer.h"
#include "idcscoresservice.h"

class ICreateDSCTurnValues :
        public ICreateDCTurnValues<const DSCContext::DartsScoreTurnValues*,
                                          const IDSIndexService*,IDCScoresService*,
                                          const IDartsInputSuggestion*>
{
public:
    virtual const DSCContext::DartsScoreTurnValues *createTurnValues(const IDSIndexService *indexService,
                                                                     IDCScoresService *playerScoreService,
                                                                     const IDartsInputSuggestion *logisticService) const = 0;
};

#endif // IBUILDDARTSSCORECONTROLLERVALUES_H
