#include "sortdartsinputs.h"

#include <DartsModelsContext/Contracts/PredicateSLAs/imodelpredicate.h>

QVector<IModel<QUuid> *> SortDartsInputs::sort(const QVector<IModel<QUuid> *> &unsortedInputs, const IModelPredicate *predicate) const
{
        QVector<IModel<QUuid>*> sortedList = unsortedInputs;
        std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
        return sortedList;
}


bool SortDartsInputs::ComparePredicate::operator()(IModel<QUuid> *_first, IModel<QUuid> *_second)
{
        return _predicate->operator()(_first,_second);
}
