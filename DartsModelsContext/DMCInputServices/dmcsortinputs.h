#ifndef DMCSORTINPUTS_H
#define DMCSORTINPUTS_H

#include "DartsModelsContext/DMCInputSLAs/isortinputmodels.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include <quuid.h>
#include "ModelsContext/MCPredicateSLAs/imodelpredicate.h"

class DMCSortInputs : public ISortInputModels
{
    // IBinaryService interface
public:
    typedef IModelPredicate<IModel<QUuid>> Predicate;
    QVector<const IModel<QUuid>*> sort(const QVector<const IModel<QUuid>*> &unsortedInputs,
                                       const IModelPredicate<IModel<QUuid>> *predicate) const override
    {
        QVector<const IModel<QUuid>*> sortedList = unsortedInputs;
        std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
        return sortedList;
    }
private:
    class ComparePredicate
    {
    public:
        ComparePredicate(const Predicate* predicate):
            _predicate(predicate){}
        bool operator()(const IModel<QUuid>* _first, const IModel<QUuid>* _second)
        {
            return _predicate->operator()(_first,_second);
        }
    private:
        const Predicate* _predicate;
    };
};
#endif // GETORDEREDDARTSSCOREMODELS_H
