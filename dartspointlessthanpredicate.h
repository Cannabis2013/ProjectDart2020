#ifndef DARTSPOINTLESSTHANPREDICATE_H
#define DARTSPOINTLESSTHANPREDICATE_H

#include "dartspointinput.h"
#include "predicate.h"

namespace DartsModelsContext {
    class DartsPointLessThanPredicate : public Predicate
    {
    public:
        bool operator ()(const IDartsInput *_first, const IDartsInput* _second) const override
        {
            auto firstModel = dynamic_cast<const IDartsPointInput*>(_first);
            auto secondModel = dynamic_cast<const IDartsPointInput*>(_second);
            if(firstModel->roundIndex() < secondModel->roundIndex())
                return true;
            else if(secondModel->roundIndex() >= secondModel->roundIndex())
                return false;
            else if(firstModel->setIndex() < secondModel->setIndex())
                return true;
            else if(firstModel->setIndex() > secondModel->setIndex())
                return false;
            else if(firstModel->attempt() < secondModel->attempt())
                return true;
            else
                return false;
        }
    };
}

#endif // DARTSPOINTLESSTHANPREDICATE_H
