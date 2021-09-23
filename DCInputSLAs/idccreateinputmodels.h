#ifndef IDCCREATEINPUTMODELS_H
#define IDCCREATEINPUTMODELS_H

#include "DCInputSLAs/idcinputmodel.h"
#include "DCScoresSLAs/idcscoresservice.h"
#include "DCJsonSLAs/ijsonvaluesextractor.h"
#include "DCInputSLAs/idccreateinputmodel.h"

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
