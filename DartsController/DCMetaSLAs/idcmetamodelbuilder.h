#ifndef IDCMETAMODELBUILDER_H
#define IDCMETAMODELBUILDER_H
#include "idcmetainfo.h"
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class IDCMetaModelBuilder
{
public:
    virtual DCMeta buildMeta(IDCMetaInfo *meta, const DCIndex &index, IDCScoreModels *scoreModels) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
