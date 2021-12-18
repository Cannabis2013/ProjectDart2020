#ifndef DPCUPDATESCORERANGE_H
#define DPCUPDATESCORERANGE_H
#include "PlayerStatsSLAs/absdcsetiptstats.h"
#include "PlayerStatsSLAs/idcstatscontext.h"
#include "Models/dcinput.h"
#include "Models/dcindex.h"
#include "Models/dcplayerstats.h"
#include <QRegExp>
class DPCUpdateScoreRange : public AbsDCSetIptStats
{
public:
    DPCUpdateScoreRange(IDCStatsContext *statsContext):
        AbsDCSetIptStats(statsContext){}
    virtual void set(DCInput &input, const DCIndex &idx, const int &initRemScore) const override
    {
        auto playerStat = &statsContext()->stat(input.playerName);
        evaulateAndUpdateStats(playerStat,input.score);
        setInputRangeStats(input,playerStat);
        input.mid = middleValue(idx,input.remScore,initRemScore);
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
    void evaulateAndUpdateStats(DCPlayerStats *stats, const int &score) const
    {
        if(stats->min > score || stats->min == -1)
            stats->min = score;
        if(stats->max < score)
            stats->max = score;
    }
    void setInputRangeStats(DCInput &input, DCPlayerStats *playerStat) const
    {
        input.min = playerStat->min;
        input.max = playerStat->max;
    }
};
#endif // DCUPDATESCORERANGE_H
