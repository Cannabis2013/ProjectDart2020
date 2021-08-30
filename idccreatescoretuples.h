#ifndef IDCCREATESCORETUPLES_H
#define IDCCREATESCORETUPLES_H

#include <dptuple.h>
#include <idartsmetadata.h>
#include <idcplayer.h>
#include <qvector.h>

class IDCCreateScoreTuples
{
public:
    typedef QVector<const DCContext::IDCPlayer*> PlayerModels;
    virtual QVector<DCContext::DCPTuple> createTuples(const PlayerModels& models, const IDartsMetaData *dartsMeta) = 0;
};
#endif // IDCCREATESCORETUPLES_H
