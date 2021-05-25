#ifndef DARTSPOINTMODELHINTSERVICE_H
#define DARTSPOINTMODELHINTSERVICE_H

#include "ibinaryservice.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class SetDartsInputHintService :
            public IBinaryService<const IDartsInput*,const int&, const IDartsInput*>
    {
    public:
        const IDartsInput* service(const IDartsInput* model, const int& hint) override
        {
            auto alteredModel = const_cast<IDartsInput*>(model);
            alteredModel->setHint(hint);
            return alteredModel;
        }
    };
}


#endif // DARTSPOINTMODELHINTSERVICE_H
