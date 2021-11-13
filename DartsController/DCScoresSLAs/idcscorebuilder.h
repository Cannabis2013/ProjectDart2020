#ifndef IDCSCOREBUILDER_H
#define IDCSCOREBUILDER_H
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class IDCScoreBuilder
{
public:
    typedef IModel<QUuid> Player;
    typedef QVector<Player*> Players;
    virtual QVector<DCScoreModel> createScores(const Players &models, const int &initialScore) const = 0;
};
#endif // IDCSCOREBUILDER_H
