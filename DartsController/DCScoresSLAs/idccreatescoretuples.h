#ifndef IDCCREATESCORETUPLES_H
#define IDCCREATESCORETUPLES_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCPlayerSLAs/idcplayer.h"
#include <qvector.h>

class IDCCreateScoreTuples
{
public:
    typedef QVector<const DCContext::IDCPlayer*> PlayerModels;
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels& models, const int &initialScore) = 0;
};
#endif // IDCCREATESCORETUPLES_H
