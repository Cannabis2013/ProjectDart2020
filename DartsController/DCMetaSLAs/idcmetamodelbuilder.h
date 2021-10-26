#ifndef IDCMETAMODELBUILDER_H
#define IDCMETAMODELBUILDER_H
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "idctournamentid.h"
#include "idcwinnerservice.h"
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class IDCMetaModelBuilder
{
public:
    virtual DCMetaInfo buildMeta(const IDCTournamentId *IdService, const DCIndex &index,
                                 IDCScoreModels *scoreModels, const DCPlayer &winner) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
