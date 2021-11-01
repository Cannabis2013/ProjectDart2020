#ifndef IDCPLAYERSTATS_H
#define IDCPLAYERSTATS_H
#include <qvector.h>
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCPlayerServices/dcplayer.h"
#include "dcplayerstat.h"
class IDCPlayerStats
{
public:
    virtual void setPlayers(const QVector<DCPlayer> &players) = 0;
    virtual DCPlayerStat &stat(const QUuid &playerId) = 0;
    virtual QVector<DCPlayerStat> &stats() = 0;
    virtual void reset() = 0;
};
#endif // IDCSTATSBUILDER_H
