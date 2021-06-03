#ifndef DARTSPOINTMODELHINTSERVICE_H
#define DARTSPOINTMODELHINTSERVICE_H

#include "ibinaryservice.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsInputModelHintService :
            public IBinaryService<const IPlayerInput*,const int&, const IPlayerInput*>
    {
    public:
        const IPlayerInput* service(const IPlayerInput* model, const int& hint) override
        {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            auto mutableModel = const_cast<IPlayerInput*>(inputModel);
            mutableModel->setHint(hint);
            return mutableModel;
        }
    };
}


#endif // DARTSPOINTMODELHINTSERVICE_H
