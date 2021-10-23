#ifndef IDCSCOREBUILDER_H
#define IDCSCOREBUILDER_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include <qvector.h>
#include "DartsController/DCPlayerServices/dcplayer.h"

class IDCScoreBuilder
{
public:
    virtual QVector<DCScoreModel> buildScores(const QVector<DCPlayer>& models, const int &initialScore) = 0;
};
#endif // IDCSCOREBUILDER_H
