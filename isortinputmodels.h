#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H

#include <qvector.h>
#include "iplayerinput.h"
#include "ipredicate.h"

class ISortInputModels
{
public:
    virtual QVector<const IPlayerInput*> sort(const QVector<const IPlayerInput*>& unsortedInputs,
                                              const IPredicate<IPlayerInput> *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
