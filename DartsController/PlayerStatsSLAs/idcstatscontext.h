#ifndef IDCSTATSCONTEXT_H
#define IDCSTATSCONTEXT_H
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "dcplayerstat.h"
class IDCStatsContext
{
public:
    typedef IPlayerModel Player;
    typedef QVector<Player*> Players;
    virtual void setPlayers(const Players &players) = 0;
    virtual DCPlayerStat &stat(const QUuid &playerId) = 0;
    virtual QVector<DCPlayerStat> &stats() = 0;
    virtual void reset() = 0;
};
#endif // IDCSTATSBUILDER_H
