#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H
#include <qvector.h>
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "ModelsContext/PredicateSLAs/imodelpredicate.h"
class ISortInputModels
{
public:
    virtual QVector<IModel<QUuid>*> sort(const QVector<IModel<QUuid>*>& unsortedInputs,
                                         const IModelPredicate *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
