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
            auto alteredModel = const_cast<IPlayerInput*>(model);
            alteredModel->setHint(hint);
            return alteredModel;
        }
    };
}


#endif // DARTSPOINTMODELHINTSERVICE_H
