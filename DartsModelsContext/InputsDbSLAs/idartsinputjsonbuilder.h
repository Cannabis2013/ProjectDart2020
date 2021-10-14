#ifndef IDARTSINPUTJSONBUILDER_H
#define IDARTSINPUTJSONBUILDER_H

#include <quuid.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class IDartsInputJsonBuilder
{
public:
    virtual QByteArray dartsInputJson(IModel<QUuid> *model) const = 0;
    virtual QByteArray dartsInputsJson(const QVector<IModel<QUuid>*> &models) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUTS_H
