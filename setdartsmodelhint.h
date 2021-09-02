#ifndef SETDARTSSCOREMODELHINT_H
#define SETDARTSSCOREMODELHINT_H

#include "ibinaryservice.h"
#include "idartsinput.h"

namespace ModelsContext
{
    class SetDartsModelHint :
            public IBinaryService<const IDartsInput*,const int&,const IDartsInput*>
    {
        // IBinaryService interface
    public:
        const IDartsInput* service(const IDartsInput*model, const int& hint) override
        {
            auto alteredModel = const_cast<IDartsInput*>(model);
            alteredModel->setHint(hint);
            return alteredModel;
        }
    };
}


#endif // SETDARTSSCOREMODELHINT_H
