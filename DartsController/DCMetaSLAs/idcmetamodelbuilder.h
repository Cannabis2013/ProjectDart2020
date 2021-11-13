#ifndef IDCMETAMODELBUILDER_H
#define IDCMETAMODELBUILDER_H
#include "idcmetainfo.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class IDCMetaModelBuilder
{
public:
    virtual DCMeta create(IDCMetaInfo *meta, IDartsIndex *index, IDCScoreModels *scoreModels) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
