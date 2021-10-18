#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include <quuid.h>
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "iscoresservice.h"

class IDCScoresService : public IScoresService<DCContext::DCScoreModel>
{
public:
    virtual DartsScoreModels &scoreModels() = 0;
};
#endif // IDARTSSCORES_H
