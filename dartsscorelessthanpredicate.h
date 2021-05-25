#ifndef DARTSSCORELESSTHANPREDICATE_H
#define DARTSSCORELESSTHANPREDICATE_H

#include "dartsscoreinput.h"
#include "predicate.h"

namespace DartsModelsContext {
    class DartsScoreLessThanPredicate : public Predicate
    {
    public:
        bool operator ()(const IDartsInput* _first, const IDartsInput* _second) const override
        {
            auto firstModel = dynamic_cast<const IDartsScoreInput*>(_first);
            auto secondModel = dynamic_cast<const IDartsScoreInput*>(_second);
            if(firstModel->roundIndex() < secondModel->roundIndex())
                return true;
            else if(secondModel->roundIndex() >= secondModel->roundIndex())
                return false;
            else if(firstModel->setIndex() < secondModel->setIndex())
                return true;
            else
                return false;
        }
    };
}

#endif // DARTSSCORELESSTHANPREDICATE_H
