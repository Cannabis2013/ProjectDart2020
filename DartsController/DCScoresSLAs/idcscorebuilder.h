#ifndef IDCSCOREBUILDER_H
#define IDCSCOREBUILDER_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include <qvector.h>
#include "DartsController/DCPlayerServices/dcplayer.h"

class IDCScoreBuilder
{
public:
    virtual QVector<DCScoreModel> createScores(const QVector<DCPlayer>& models, const int &initialScore) const = 0;
};
#endif // IDCSCOREBUILDER_H
