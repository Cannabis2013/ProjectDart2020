#ifndef GETORDEREDDARTSSCOREMODELS_H
#define GETORDEREDDARTSSCOREMODELS_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include "idartsscoredb.h"
#include <quuid.h>
#include "ipredicate.h"

namespace DartsModelsContext
{   
    class SortPlayerInputsByPredicate :
            public IBinaryService<const QVector<const IPlayerInput*>&,
                                  const IPredicate*,
                                  QVector<const IPlayerInput*>>
    {
        // IBinaryService interface
    public:
        QVector<const IPlayerInput*> service(const QVector<const IPlayerInput*>& dartsPointModels,
                                             const IPredicate* predicate) override
        {
            QVector<const IPlayerInput*> sortedList = dartsPointModels;
            std::sort(sortedList.begin(),sortedList.end(),ComparePredicate(predicate));
            return dartsPointModels;
        }
    private:
        class ComparePredicate
        {
        public:
            ComparePredicate(const IPredicate* predicate):
                _predicate(predicate){}
            bool operator()(const IDartsInput* _first, const IDartsInput* _second)
            {
                return _predicate->operator()(_first,_second);
            }
        private:
            const IPredicate* _predicate;
        };
    };
}


#endif // GETORDEREDDARTSSCOREMODELS_H
