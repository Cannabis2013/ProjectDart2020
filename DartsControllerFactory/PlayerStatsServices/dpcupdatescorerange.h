#ifndef DPCUPDATESCORERANGE_H
#define DPCUPDATESCORERANGE_H
#include "PlayerStatsSLAs/idcupdatescorerange.h"
#include "PlayerStatsSLAs/idcstatistics.h"
#include "Models/dcinput.h"
#include "Models/dcindex.h"
#include "Models/dcstatsmodel.h"
#include <QRegExp>
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"
class DPCUpdateScoreRange : public IDCUpdateScoreRange
{
public:
    DPCUpdateScoreRange(DCServices *services):_services(services){}
    void update(DCInput &input) const override
    {
        auto idx = _services->indexService()->index();
        auto meta = _services->metaService()->meta();
        auto statsModel = &_services->statisticsService()->stat(input.playerName);
        evaulateAndUpdateStats(statsModel,input.score);
        setInputRangeStats(input,statsModel);
        input.mid = middleValue(idx,input.remScore,meta.initRemScore);
    }
private:
    double middleValue(const DCIndex &idx, const int &remainingScore, const int &initialScore) const
    {
        auto scoresAccumulated = initialScore - remainingScore;
        auto divisor = idx.roundIndex*3 + idx.attemptIndex - 2;
        auto mid = (double)scoresAccumulated/divisor;
        return toTwoDecimals(mid);
    }
    double toTwoDecimals(const double &value) const
    {
        auto stringVal = QString::number(value);
        QRegExp reg("\\d+.\\d{2}");
        auto pos = reg.indexIn(stringVal);
        if(pos == -1)
            return stringVal.toDouble();
        return reg.cap(0).toDouble();
    }
    void evaulateAndUpdateStats(DCStatsModel *stats, const int &score) const
    {
        if(stats->min > score || stats->min == -1)
            stats->min = score;
        if(stats->max < score)
            stats->max = score;
    }
    void setInputRangeStats(DCInput &input, DCStatsModel *playerStat) const
    {
        input.min = playerStat->min;
        input.max = playerStat->max;
    }
    DCServices *_services;
};
#endif // DCUPDATESCORERANGE_H
