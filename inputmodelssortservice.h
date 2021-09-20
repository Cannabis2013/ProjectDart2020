#ifndef GETORDEREDDARTSSCOREMODELS_H
#define GETORDEREDDARTSSCOREMODELS_H

#include "isortinputmodels.h"
#include "idartsinput.h"
#include "ModelsContext/imodelsdbcontext.h"
#include <quuid.h>
#include "ipredicate.h"

class InputModelsSortService : public ISortInputModels
{
    // IBinaryService interface
public:
    typedef IPredicate<IModel<QUuid>> Predicate;
    QVector<const IModel<QUuid>*> sort(const QVector<const IModel<QUuid>*> &unsortedInputs,
                                       const IPredicate<IModel<QUuid>> *predicate) const override
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
