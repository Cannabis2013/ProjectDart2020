#ifndef GETORDEREDDARTSSCOREMODELS_H
#define GETORDEREDDARTSSCOREMODELS_H

#include "isortinputmodels.h"
#include "idartsscoreinput.h"
#include "idartsinputdb.h"
#include <quuid.h>
#include "ipredicate.h"

namespace DartsModelsContext
{
    class InputModelsSortService : public ISortInputModels
    {
        // IBinaryService interface
    public:
        typedef IPredicate<IPlayerInput> Predicate;
        QVector<const IPlayerInput *> sort(const QVector<const IPlayerInput *> &unsortedInputs, const IPredicate<IPlayerInput> *predicate) const override
        {
            QVector<const IPlayerInput*> sortedList = unsortedInputs;
            std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
            return sortedList;
        }
    private:
        class ComparePredicate
        {
        public:
            ComparePredicate(const Predicate* predicate):
                _predicate(predicate){}
            bool operator()(const IPlayerInput* _first, const IPlayerInput* _second)
            {
                return _predicate->operator()(_first,_second);
            }
        private:
            const Predicate* _predicate;
        };
    };
}


#endif // GETORDEREDDARTSSCOREMODELS_H
