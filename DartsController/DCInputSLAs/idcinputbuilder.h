#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H

#include "DartsController/DCInputSLAs/idcinput.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCInputBuilder
{
public:
    virtual IDCInput *createModel(const QByteArray &json) const = 0;
    virtual IDCInput *createModel(const DCContext::DCScoreModel &scoreModel) const = 0;
    virtual QVector<IDCInput*> createModels(IDCScoresService *scoresService) const = 0;
    virtual QVector<IDCInput*> createModels(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H
