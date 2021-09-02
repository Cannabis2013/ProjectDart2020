#ifndef DARTSPOINTLESSTHANPREDICATE_H
#define DARTSPOINTLESSTHANPREDICATE_H

#include "dartsinput.h"
#include "ipredicate.h"

namespace ModelsContext {
    class SortDartsPointInputsByIndexes : public IPredicate<IModel<QUuid>>
    {
    public:
        bool operator ()(const IModel<QUuid> *_first, const IModel<QUuid>* _second) const override
        {
            auto firstModel = dynamic_cast<const IDartsInput*>(_first);
            auto secondModel = dynamic_cast<const IDartsInput*>(_second);
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
