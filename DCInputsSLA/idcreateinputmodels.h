#ifndef IDCREATEINPUTMODELS_H
#define IDCREATEINPUTMODELS_H

#include "DCInputsSLA/idcinputmodel.h"
#include "idcscoresservice.h"
#include "ijsonvaluesextractor.h"
#include "idccreateinputmodel.h"

class IDCCreateInputModels
{
public:
    virtual QVector<DCContext::IDCInputModel*> createModels(IDCScoresService *scoresService,
                                                            const IDCCreateInputModel *modelBuilder) const = 0;
    virtual QVector<DCContext::IDCInputModel*> createModels(const QByteArray &json,
                                                            const IJsonValuesExtractor *extractor,
                                                            const IDCCreateInputModel *modelBuilder) const = 0;
};

#endif // IDCREATEINPUTMODELS_H
