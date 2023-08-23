#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H

#include <DartsModelsContext/Contracts/PredicateSLAs/imodelpredicate.h>
#include <quuid.h>

class ISortInputModels
{
public:
    virtual QVector<IModel<QUuid>*> sort(const QVector<IModel<QUuid>*>& unsortedInputs,
                                         const IModelPredicate *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
