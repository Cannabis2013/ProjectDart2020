#ifndef IDCCREATESCORETUPLES_H
#define IDCCREATESCORETUPLES_H

#include <dcscoremodel.h>
#include <idcinitialscore.h>
#include <idcplayer.h>
#include <qvector.h>

class IDCCreateScoreTuples
{
public:
    typedef QVector<const DCContext::IDCPlayer*> PlayerModels;
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels& models, const IDCInitialScore *dartsMeta) = 0;
};
#endif // IDCCREATESCORETUPLES_H
