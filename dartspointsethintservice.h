#ifndef DARTSPOINTMODELHINTSERVICE_H
#define DARTSPOINTMODELHINTSERVICE_H

#include "ibinaryservice.h"
#include "idartspointinput.h"

class DartsPointSetHintService :
        public IBinaryService<const DartsModelsContext::IDartsPointInput*,const int&, const DartsModelsContext::IDartsPointInput*>
{
public:
    const DartsModelsContext::IDartsPointInput* service(const DartsModelsContext::IDartsPointInput* model, const int& hint) override
    {
        auto alteredModel = const_cast<DartsModelsContext::IDartsPointInput*>(model);
        alteredModel->setHint(hint);
        return alteredModel;
    }
};

#endif // DARTSPOINTMODELHINTSERVICE_H
