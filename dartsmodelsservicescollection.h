#ifndef DARTSMODELSSERVICESCOLLECTION_H
#define DARTSMODELSSERVICESCOLLECTION_H

#include "iunaryservice.h"
#include "ibinaryservice.h"
#include <quuid.h>
#include "abstractdartstournament.h"
#include "iplayermodel.h"
#include "idartspointinput.h"

typedef IUnaryService<const QByteArray&,const IDartsInput*> AssembleDartsPointService;
typedef IUnaryService<const QByteArray&,const IPlayerModel*> AssemblePlayerModelService;
typedef IBinaryService<const AbstractDartsTournament*,
                       const QVector<QUuid>&,
                       const AbstractDartsTournament*> AssignPlayerIdsService;

#endif // DARTSMODELSSERVICESCOLLECTION_H
