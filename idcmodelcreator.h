#ifndef IDCMODELCREATOR_H
#define IDCMODELCREATOR_H

#include <idcmodel.h>
#include "idcscoresservice.h"
#include "ijsonvaluesextractor.h"

class IDCModelCreator
{
public:
    virtual DCContext::IDCModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const = 0;
    virtual QVector<DCContext::IDCModel*> createModels(IDCScoresService *scoresService) const = 0;
    virtual QVector<DCContext::IDCModel*> createModels(const QByteArray &json, const IJsonValuesExtractor *extractor) const = 0;
};
#endif // IDPCMODELCREATOR_H
