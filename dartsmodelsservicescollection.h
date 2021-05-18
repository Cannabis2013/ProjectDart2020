#ifndef DARTSMODELSSERVICESCOLLECTION_H
#define DARTSMODELSSERVICESCOLLECTION_H

#include "iunaryservice.h"
#include "ibinaryservice.h"
#include <quuid.h>
#include "idartstournament.h"
#include "iplayermodel.h"
#include "idartspointinput.h"

typedef IUnaryService<const QByteArray&,const DartsModelsContext::IDartsPointInput*> AssembleDartsPointService;
typedef IUnaryService<const QByteArray&,const IPlayerModel*> AssemblePlayerModelService;
typedef IBinaryService<const IDartsTournament*,
                       const QVector<QUuid>&,
                       const IDartsTournament*> AssignPlayerIdsService;

#endif // DARTSMODELSSERVICESCOLLECTION_H
