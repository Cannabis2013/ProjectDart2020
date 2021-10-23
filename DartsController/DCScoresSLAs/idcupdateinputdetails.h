#ifndef IDCUPDATEINPUTDETAILS_H
#define IDCUPDATEINPUTDETAILS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCInputStatsSLAs/idcscorestats.h"

class IDCUpdateInputDetails
{
public:
    virtual void update(const QVector<DCInput> &inputs,IDCScoreStats *statsController,
                        IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
