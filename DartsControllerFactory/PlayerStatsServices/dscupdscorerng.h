#ifndef DSCUPDSCORERNG_H
#define DSCUPDSCORERNG_H
#include "PlayerStatsSLAs/idcsetiptstats.h"
#include "PlayerStatsSLAs/idcstatistics.h"
#include "Models/dcindex.h"
#include "Models/dcinput.h"
#include <qregexp.h>
#include "Models/dcplayerstats.h"
class DSCUpdScoreRng : public IDCSetIptStats
{
public:
    void set(DCInput &input, const DCIndex &idx, const int &initRemScore, IDCStatistics *statsContext) const override
    {
        auto playerStat = &statsContext->stat(input.playerName);
        evaluateAndUpdateStats(playerStat,input.score);
        setInputRangeStats(input,playerStat);
        input.mid = middleValue(idx,input.remScore,initRemScore);
    }
private:
    double middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const
    {
        auto scoresAccumulated = initialScore - remainingScore;
        auto roundIndex = index.roundIndex;
        auto midVal = (double)scoresAccumulated/roundIndex;
        return toTwoDecimals(midVal);
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
    void evaluateAndUpdateStats(DCPlayerStats *stats, const int &score) const
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
#endif // DSCUPDSCORERNG_H
