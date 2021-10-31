#ifndef IDCUPDATEPLAYERSCORES_H
#define IDCUPDATEPLAYERSCORES_H

#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/PlayerStatsSLAs/idcplayerstats.h"
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"

class IDCUpdatePlayerScores
{
public:
    virtual void update(const QVector<DCInput> &inputs, IDCScoreModels *scoresService) const = 0;
};
#endif // IDARTSSUBTRACTSCORES_H