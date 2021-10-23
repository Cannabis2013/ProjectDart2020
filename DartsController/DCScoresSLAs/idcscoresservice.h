#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include <quuid.h>
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "iscoresservice.h"
#include "DartsController/DCInputServices/dcinput.h"

class IDCScoresService : public IScoresService<DCScoreModel>
{
public:
    virtual DCScoreModel scoreModel(const QUuid &playerId) const = 0;
    virtual DartsScoreModels &scoreModels() = 0;
    virtual void updatePlayerRemainingScore(const DCInput &input) = 0;
    virtual DCScoreModel subtractAndUpdate(const DCInput &input) = 0;
    virtual DCScoreModel addAndUpdate(const DCInput &input) = 0;
};
#endif // IDARTSSCORES_H
