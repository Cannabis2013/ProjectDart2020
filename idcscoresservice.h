#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include <idartsmetadata.h>
#include <idcplayer.h>
#include <quuid.h>
#include "dptuple.h"
#include "iscoresservice.h"

class IDCScoresService : public IScoresService<const DCContext::IDCPlayer*, DCContext::DCPTuple,IDartsMetaData>
{
public:
    virtual const DartsPlayerTuples &tuples() = 0;
    virtual void resetTuples(const IDartsMetaData *metaService) = 0;
};
#endif // IDARTSSCORES_H
