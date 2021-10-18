#ifndef IDCMETAJSONBUILDER_H
#define IDCMETAJSONBUILDER_H

#include "idctournamentid.h"
#include "idcwinnerservice.h"
#include <qjsonobject.h>
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"

class IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const IDCPlayerService *playerService,
                           const IDCWinnerService *winnerService,const IDCIndexService *indexContext,
                           IDCScoresService *scoresContext) const = 0;
};
#endif // IDCMETAJSONBUILDER_H
