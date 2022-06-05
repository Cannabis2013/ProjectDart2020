#ifndef DARTSPOINTLESSTHANPREDICATE_H
#define DARTSPOINTLESSTHANPREDICATE_H

#include <DartsModelsContext/PredicateSLAs/imodelpredicate.h>

class SortDartsInputsByIndexes : public IModelPredicate
{
public:
    bool operator ()(const IModel<QUuid> *_first, const IModel<QUuid>* _second) const override;
};
#endif // DARTSPOINTLESSTHANPREDICATE_H
