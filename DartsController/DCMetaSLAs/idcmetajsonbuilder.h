#ifndef IDCMETAJSONBUILDER_H
#define IDCMETAJSONBUILDER_H

#include "idctournamentid.h"
#include "idcwinnerservice.h"
#include <qjsonobject.h>
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const DCPlayer &winner,
                           const DCIndex &index, IDCScoreModels *scoresContext) const = 0;
};
#endif // IDCMETAJSONBUILDER_H
