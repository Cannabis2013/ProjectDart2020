#ifndef IDCCREATEINPUTMODELS_H
#define IDCCREATEINPUTMODELS_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCJsonSLAs/ijsonvaluesextractor.h"
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"

class IDCCreateInputModels
{
public:
    virtual QVector<DCContext::IDCInputModel*> createModels(IDCScoresService *scoresService,
                                                            const IDCCreateInputModel *modelBuilder) const = 0;
    virtual QVector<DCContext::IDCInputModel*> createModels(const QByteArray &json,
                                                            const IDCInputJsonKeys *jsonKeys,
                                                            const IDCCreateInputModel *modelBuilder) const = 0;
};
#endif // IDCCREATEINPUTMODELS_H
