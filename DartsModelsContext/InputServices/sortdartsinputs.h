#ifndef SORTDARTSINPUTS_H
#define SORTDARTSINPUTS_H
#include "DartsModelsContext/InputSLAs/isortinputmodels.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include <quuid.h>
#include "ModelsContext/MCPredicateSLAs/imodelpredicate.h"
class SortDartsInputs : public ISortInputModels
{
public:
    QVector<IModel<QUuid>*> sort(const QVector<IModel<QUuid>*> &unsortedInputs,
                                       const IModelPredicate *predicate) const override
    {
        QVector<IModel<QUuid>*> sortedList = unsortedInputs;
        std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
        return sortedList;
    }
private:
    class ComparePredicate
    {
    public:
        ComparePredicate(const IModelPredicate* predicate):
            _predicate(predicate){}
        bool operator()(IModel<QUuid>* _first, IModel<QUuid>* _second)
        {
            return _predicate->operator()(_first,_second);
        }
    private:
        const IModelPredicate* _predicate;
    };
};
#endif // GETORDEREDDARTSSCOREMODELS_H
