#ifndef IDCMODELCREATOR_H
#define IDCMODELCREATOR_H

#include <idcmodel.h>
#include "idcscoresservice.h"

class IDCModelCreator
{
public:
    virtual DCContext::IDCModel *createModel(const QByteArray &json) const = 0;
    virtual DCContext::IDCModel *createModel(const int &score, const int &point = 0, const int &modKeyCode = -1) const = 0;
    virtual QVector<DCContext::IDCModel*> createModels(IDCScoresService *scoresService) const = 0;
    virtual QVector<DCContext::IDCModel*> createModels(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H
