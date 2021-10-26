#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H
#include <quuid.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"
struct IModelPredicate{
    virtual bool operator()(const IModel<QUuid>* first, const IModel<QUuid> *second) const = 0;
};
#endif // IPLAYERINPUTCOMPARISON_H
