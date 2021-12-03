#ifndef IDCSTATSCONTEXT_H
#define IDCSTATSCONTEXT_H
#include <qstringlist.h>
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "dcplayerstat.h"
class IDCStatsContext
{
public:
    virtual void setPlayers(const QStringList &players) = 0;
    virtual DCPlayerStat &stat(const QString &name) = 0;
    virtual QVector<DCPlayerStat> &stats() = 0;
    virtual void reset() = 0;
};
#endif // IDCSTATSBUILDER_H
