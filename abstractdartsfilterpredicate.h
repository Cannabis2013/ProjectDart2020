#ifndef IFILTERPREDICATE_H
#define IFILTERPREDICATE_H

#include "idartsinput.h"
#include <qvector.h>

namespace DartsModelsContext {
    class AbstractDartsFilterPredicate
    {
    public:
        typedef AbstractDartsFilterPredicate Predicate;
        virtual Predicate& operator+=(const Predicate *predicate)
        {
            _predicates << predicate;
            return *this;
        }
        bool doMatch(const IDartsInput* input) const
        {
            auto result = this->match(input);
            for (const auto& predicate : _predicates)
                result = predicate->doMatch(input);
            return result;
        }
        virtual bool match(const IDartsInput*) const = 0;
    private:
        QVector<const Predicate*> _predicates;
    };
}


#endif // IFILTERPREDICATE_H
