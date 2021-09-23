#ifndef IDCCREATESCORETUPLES_H
#define IDCCREATESCORETUPLES_H

#include "DCScoresServices/dcscoremodel.h"
#include "DCMetaSLAs/idcinitialscore.h"
#include "DCPlayerSLAs/idcplayer.h"
#include <qvector.h>

class IDCCreateScoreTuples
{
public:
    typedef QVector<const DCContext::IDCPlayer*> PlayerModels;
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels& models, const int &initialScore) = 0;
};
#endif // IDCCREATESCORETUPLES_H
