#ifndef SORTDARTSSCOREINPUTSBYINDEXES_H
#define SORTDARTSSCOREINPUTSBYINDEXES_H

#include "dartsscoreinput.h"
#include "ipredicate.h"

namespace ModelsContext {
    class SortDartsScoreInputsByIndexes : public IPredicate<IModel<QUuid>>
    {
    public:
        typedef IPredicate<IPlayerInput> Predicate;
        bool operator ()(const IModel<QUuid> *_first, const IModel<QUuid>* _second) const override
        {
            auto firstModel = dynamic_cast<const IDartsScoreInput*>(_first);
            auto secondModel = dynamic_cast<const IDartsScoreInput*>(_second);
            if(firstModel->roundIndex() < secondModel->roundIndex())
                return true;
            else if(secondModel->roundIndex() >= secondModel->roundIndex())
                return false;
            else if(firstModel->setIndex() < secondModel->setIndex())
                return true;
            else if(firstModel->setIndex() > secondModel->setIndex())
                return false;
            else
                return false;
        }
    };
}

#endif // SORTDARTSSCOREINPUTSBYINDEXES_H
