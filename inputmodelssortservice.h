#ifndef GETORDEREDDARTSSCOREMODELS_H
#define GETORDEREDDARTSSCOREMODELS_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include "idartsinputdb.h"
#include <quuid.h>
#include "ipredicate.h"

namespace DartsModelsContext
{   
    class InputModelsSortService :
            public IBinaryService<const QVector<const IPlayerInput*>&,
                                  const IPredicate<IPlayerInput>*,
                                  QVector<const IPlayerInput*>>
    {
        // IBinaryService interface
    public:
        typedef IPredicate<IPlayerInput> Predicate;
        QVector<const IPlayerInput*> service(const QVector<const IPlayerInput*>& dartsPointModels,
                                             const Predicate* predicate) override
        {
            QVector<const IPlayerInput*> sortedList = dartsPointModels;
            std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
            return dartsPointModels;
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
