#ifndef IDCCREATESCORETUPLES_H
#define IDCCREATESCORETUPLES_H

#include <dcscoremodel.h>
#include <idcmetadata.h>
#include <idcplayer.h>
#include <qvector.h>

class IDCCreateScoreTuples
{
public:
    typedef QVector<const DCContext::IDCPlayer*> PlayerModels;
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels& models, const IDCMetaData *dartsMeta) = 0;
};
#endif // IDCCREATESCORETUPLES_H
