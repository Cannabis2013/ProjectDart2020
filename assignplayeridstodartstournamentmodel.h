#ifndef ASSEMBLEPLAYERIDSFROMPLAYERINDEXES_H
#define ASSEMBLEPLAYERIDSFROMPLAYERINDEXES_H

#include "ibinaryservice.h"
#include "qvector.h"
#include "iplayermodelsservice.h"
#include "idartstournament.h"

class AssignPlayerIdsToDartsTournamentModel :
        public IBinaryService<const IDartsTournament*,const QVector<QUuid>&,const IDartsTournament*>
{
public:
    const IDartsTournament* service(const IDartsTournament* model,const QVector<QUuid>&playerIds) override
    {
        auto newModel = const_cast<IDartsTournament*>(model);
        newModel->setAssignedPlayerIdentities(playerIds);
        return newModel;
    }
};

#endif // ASSEMBLEPLAYERIDSFROMPLAYERINDEXES_H
