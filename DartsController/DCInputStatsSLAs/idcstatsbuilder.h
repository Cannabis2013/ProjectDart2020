#ifndef IDCSTATSBUILDER_H
#define IDCSTATSBUILDER_H

#include <qvector.h>
#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCPlayerServices/dcplayer.h"
#include "dcinputstats.h"

class IDCStatsBuilder
{
public:
    virtual void setPlayers(const QVector<DCPlayer> &players) = 0;
    virtual DCInputStat processScore(const DCInput &score, const IDCIndexService *indexService, const int &initialScore) = 0;
};
#endif // IDCSTATSBUILDER_H
