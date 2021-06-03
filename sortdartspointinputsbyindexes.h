#ifndef DARTSPOINTLESSTHANPREDICATE_H
#define DARTSPOINTLESSTHANPREDICATE_H

#include "dartspointinput.h"
#include "ipredicate.h"

namespace DartsModelsContext {
    class SortDartsPointInputsByIndexes : public IPredicate<IPlayerInput>
    {
    public:
        typedef IPredicate<IPlayerInput> Predicate;
        bool operator ()(const IPlayerInput *_first, const IPlayerInput* _second) const override
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
