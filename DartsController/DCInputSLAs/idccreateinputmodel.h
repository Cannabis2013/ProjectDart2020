#ifndef IDCCREATEINPUTMODEL_H
#define IDCCREATEINPUTMODEL_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCCreateInputModel
{
public:
    virtual DCContext::IDCInputModel *createModel(const QByteArray &json) const = 0;
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const = 0;
    virtual QVector<DCContext::IDCInputModel*> createModels(IDCScoresService *scoresService) const = 0;
    virtual QVector<DCContext::IDCInputModel*> createModels(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H
