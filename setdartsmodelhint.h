#ifndef SETDARTSSCOREMODELHINT_H
#define SETDARTSSCOREMODELHINT_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"

class SetDartsModelHint :
        public IBinaryService<const IDartsScoreInput*,const int&,const IDartsScoreInput*>
{
    // IBinaryService interface
public:
    const IDartsScoreInput* service(const IDartsScoreInput*model, const int& hint) override
    {
        auto alteredModel = const_cast<IDartsScoreInput*>(model);
        alteredModel->setHint(hint);
        return alteredModel;
    }
};

#endif // SETDARTSSCOREMODELHINT_H
