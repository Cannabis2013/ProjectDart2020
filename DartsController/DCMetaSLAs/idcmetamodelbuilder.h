#ifndef IDCMETAMODELBUILDER_H
#define IDCMETAMODELBUILDER_H

#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
#include "idctournamentid.h"
#include "idcwinnerservice.h"

class IDCMetaModelBuilder
{
public:
    virtual DCMetaInfo buildMeta(const IDCTournamentId *IdService, const DCIndex &index,
                                 IDCScoreModels *scoreModels, const IDCWinnerService *winnerService) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
