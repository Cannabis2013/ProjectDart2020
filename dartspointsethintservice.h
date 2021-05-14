#ifndef DARTSPOINTMODELHINTSERVICE_H
#define DARTSPOINTMODELHINTSERVICE_H

#include "ibinaryservice.h"
#include "idartspointinput.h"

class DartsPointSetHintService :
        public IBinaryService<const IDartsPointInput*,const int&, const IDartsPointInput*>
{
public:
    const IDartsPointInput* service(const IDartsPointInput* model, const int& hint) override
    {
        auto alteredModel = const_cast<IDartsPointInput*>(model);
        alteredModel->setHint(hint);
        return alteredModel;
    }
};

#endif // DARTSPOINTMODELHINTSERVICE_H
