#ifndef IDCSCORESTATS_H
#define IDCSCORESTATS_H
#include <qvector.h>
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCPlayerServices/dcplayer.h"
#include "dcplayerstat.h"
class IDCScoreStats
{
public:
    virtual void initialize(const QVector<DCPlayer> &players) = 0;
    virtual void updatePlayerStats(DCInput &score, const IDCIndexController *indexService,
                               const IDCScoresService *scoresService,const int &initialScore) = 0;
    virtual void updatePlayerStat(const DCInput &input) = 0;
    virtual QVector<DCPlayerStat> playerStats() const = 0;
};
#endif // IDCSTATSBUILDER_H
