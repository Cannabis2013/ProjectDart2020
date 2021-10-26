#ifndef IDCUPDATEINPUTDETAILS_H
#define IDCUPDATEINPUTDETAILS_H

#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/PlayerStatsSLAs/idcplayerstats.h"
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"

class IDCUpdateInputDetails
{
public:
    virtual void update(const QVector<DCInput> &inputs, IDCScoreModels *scoresService) = 0;
};
#endif // IDARTSSUBTRACTSCORES_H
