#ifndef IDCCREATEINPUTMODEL_H
#define IDCCREATEINPUTMODEL_H

#include "DCInputSLAs/idcinputmodel.h"
#include "DCScoresSLAs/idcscoresservice.h"
#include "DCJsonSLAs/ijsonvaluesextractor.h"
#include "DCInputSLAs/idcinputjsonkeys.h"
class IDCCreateInputModel
{
public:
    virtual DCContext::IDCInputModel *createModel(const QByteArray &json, const IDCInputJsonKeys *jsonKeys) const = 0;
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const = 0;
};
#endif // IDPCMODELCREATOR_H
