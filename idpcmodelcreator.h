#ifndef IDPCMODELCREATOR_H
#define IDPCMODELCREATOR_H

#include "idcmodelcreator.h"
#include <idpcmodel.h>

class IDPCModelCreator : public IDCModelCreator<DPCContext::IDPCModel,QByteArray,QUuid,QString>
{
public:
    virtual DPCContext::IDPCModel *createModel(const QByteArray &json) const = 0;
    virtual DPCContext::IDPCModel *createModel(const int &point, const int &score, const int &modKeyCode) const = 0;
    virtual QVector<DPCContext::IDPCModel*> createModels(const QByteArray &json) const = 0;
};

#endif // IDPCMODELCREATOR_H
