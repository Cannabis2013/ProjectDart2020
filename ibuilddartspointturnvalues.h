#ifndef IBUILDDARTSPOINTTURNVALUES_H
#define IBUILDDARTSPOINTTURNVALUES_H

#include "idartspointindexservice.h"
#include "iplayerpointservice.h"
#include "idartsinputsuggestion.h"
#include "dartspointturnvalues.h"
#include "idartscontrollerplayer.h"
#include "idartscontrollerpoint.h"
#include "idartspointcontrollerindexes.h"
#include "ibuildcontrollerturnvalues.h"


namespace DartsPointControllerContext {
    namespace BuildTurnValuesContext {
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
        typedef IDartsControllerPlayer<QUuid,QString,QByteArray> ControllerPlayer;
        typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerPointService;
        typedef DartsPointTurnValues TurnValuesModel;
        typedef IDartsPointControllerIndexes<QByteArray> DartsIndexes;
        typedef IDartsPointIndexService<DartsIndexes> DartsIndexService;
        typedef IDartsInputSuggestion<QString> LogisticService;
    }
    class IBuildDartsPointTurnValues : public
            IBuildControllerTurnValues<BuildTurnValuesContext::TurnValuesModel,
                                       BuildTurnValuesContext::DartsIndexService,
                                       BuildTurnValuesContext::PlayerPointService,
                                       BuildTurnValuesContext::LogisticService>
    {

        // IBuildControllerTurnValues interface
    public:
        virtual const Model *createTurnValues(const IndexService *indexService,
                                                       const InputService *playerScoreService,
                                                       const LogisticService *logisticService) const = 0;
    };
}


#endif // IBUILDTURNVALUES_H
