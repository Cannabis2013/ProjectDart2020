#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H

#include <qvector.h>
#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "ModelsContext/MCPredicateSLAs/imodelpredicate.h"

class ISortInputModels
{
public:
    virtual QVector<const IModel<QUuid>*> sort(const QVector<const IModel<QUuid>*>& unsortedInputs,
                                              const IModelPredicate<IModel<QUuid>> *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
