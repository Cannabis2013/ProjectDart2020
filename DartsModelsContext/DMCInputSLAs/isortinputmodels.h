#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H

#include <qvector.h>
#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "ipredicate.h"

class ISortInputModels
{
public:
    virtual QVector<const IModel<QUuid>*> sort(const QVector<const IModel<QUuid>*>& unsortedInputs,
                                              const IPredicate<IModel<QUuid>> *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
