#ifndef IDCMETAJSONBUILDER_H
#define IDCMETAJSONBUILDER_H

#include "idctournamentid.h"
#include <qjsonobject.h>
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"

class IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const IDCPlayerService *playerService) const = 0;
};
#endif // IDCMETAJSONBUILDER_H
