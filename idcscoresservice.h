#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include <idartsmetadata.h>
#include <idcplayer.h>
#include <quuid.h>
#include "dcscoremodel.h"
#include "iscoresservice.h"

class IDCScoresService : public IScoresService<const DCContext::IDCPlayer*, DCContext::DCScoreModel,IDartsMetaData>
{
public:
    virtual DartsScoreModels &scoreModels() = 0;
    virtual void resetTuples(const IDartsMetaData *metaService) = 0;
};
#endif // IDARTSSCORES_H
