#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include "DCMetaSLAs/idcinitialscore.h"
#include "DCPlayerSLAs/idcplayer.h"
#include <quuid.h>
#include "DCScoresServices/dcscoremodel.h"
#include "iscoresservice.h"

class IDCScoresService : public IScoresService<DCContext::DCScoreModel>
{
public:
    virtual DartsScoreModels &scoreModels() = 0;
};
#endif // IDARTSSCORES_H
