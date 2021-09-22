#ifndef IDCCREATEINPUTMODEL_H
#define IDCCREATEINPUTMODEL_H

#include "DCInputsSLA/idcinputmodel.h"
#include "idcscoresservice.h"
#include "ijsonvaluesextractor.h"

class IDCCreateInputModel
{
public:
    virtual DCContext::IDCInputModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const = 0;
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const = 0;
};
#endif // IDPCMODELCREATOR_H
