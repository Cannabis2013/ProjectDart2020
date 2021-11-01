#ifndef IDCMETAJSONBUILDER_H
#define IDCMETAJSONBUILDER_H

#include <qjsonobject.h>
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const DCMeta &metaInfo, const DCIndex &index, IDCScoreModels *scoresContext) const = 0;
};
#endif // IDCMETAJSONBUILDER_H
