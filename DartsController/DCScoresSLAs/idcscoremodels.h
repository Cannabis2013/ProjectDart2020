#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H

#include <quuid.h>
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "iscoresservice.h"
#include "DartsController/DCInputServices/dcinput.h"

class IDCScoreModels : public IScoresService<DCScoreModel>
{
public:
    virtual DCScoreModel &score(const QUuid &playerId) = 0;
    virtual DartsScoreModels &scores() = 0;
};
#endif // IDARTSSCORES_H
