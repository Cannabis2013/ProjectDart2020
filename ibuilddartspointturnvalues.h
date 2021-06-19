#ifndef IBUILDDARTSPOINTTURNVALUES_H
#define IBUILDDARTSPOINTTURNVALUES_H

#include "idartspointindexservice.h"
#include "iplayerpointservice.h"
#include "idartslogisticsservice.h"
#include "dartspointturnvalues.h"
#include "idartscontrollerplayer.h"
#include "idartscontrollerpoint.h"
#include "idartspointcontrollerindexes.h"

class IBuildDartsPointTurnValues
{
public:
    typedef DartsPointControllerContext::IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    typedef DartsPointControllerContext::IDartsControllerPlayer<QUuid,QString> ControllerPlayer;
    typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerPointService;
    typedef DartsPointControllerContext::DartsPointTurnValues TurnValuesModel;
    typedef DartsPointControllerContext::IDartsPointControllerIndexes DartsIndexes;
    typedef IDartsPointIndexService<DartsIndexes> DartsIndexService;
    virtual const TurnValuesModel* buildTurnValues(const DartsIndexService* indexService,
                                                   const PlayerPointService* playerScoreService,
                                                   const IDartsLogisticsService<QString>* logisticService) const = 0;
};

#endif // IBUILDTURNVALUES_H
