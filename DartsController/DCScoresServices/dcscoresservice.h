#ifndef DCSCORESSERVICE_H
#define DCSCORESSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class DCScoresService : public IDCScoresService
{
public:
    virtual DartsScoreModels &scoreModels() override
    {
        return _tuples;
    }
private:
    DartsScoreModels _tuples;
};
#endif // DARTSSCORES_H
