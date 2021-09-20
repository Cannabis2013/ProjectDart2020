#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include <idcinitialscore.h>
#include <idcplayer.h>
#include <quuid.h>
#include "dcscoremodel.h"
#include "iscoresservice.h"

class IDCScoresService : public IScoresService<DCContext::DCScoreModel>
{
public:
    virtual DartsScoreModels &scoreModels() = 0;
};
#endif // IDARTSSCORES_H
