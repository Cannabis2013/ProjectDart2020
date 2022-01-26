#include "dcupdatescorerange.h"
#include "Models/dcindex.h"
#include "Models/dcinput.h"
#include <qregexp.h>
#include "Models/dcstatsmodel.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"

DCUpdateScoreRange::DCUpdateScoreRange(DCServices *services):
    _services(services){}

void DCUpdateScoreRange::update(DCInput &input) const
{
    auto idx = _services->indexService()->index();
    auto meta = _services->metaService()->meta();
    auto statsModel = &_services->statisticsService()->stat(input.playerName);
    evaluateAndUpdateStats(statsModel,input.score);
    setInputRangeStats(input,statsModel);
    input.mid = middleValue(idx,input.remScore,meta.initRemScore);
}

double DCUpdateScoreRange::middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const
{
    auto scoresAccumulated = initialScore - remainingScore;
    auto roundIndex = index.roundIndex;
    auto midVal = (double)scoresAccumulated/roundIndex;
    return toTwoDecimals(midVal);
}

double DCUpdateScoreRange::toTwoDecimals(const double &value) const
{
    auto stringVal = QString::number(value);
    QRegExp reg("\\d+.\\d{2}");
    auto pos = reg.indexIn(stringVal);
    if(pos == -1)
        return stringVal.toDouble();
    return reg.cap(0).toDouble();
}

void DCUpdateScoreRange::evaluateAndUpdateStats(DCStatsModel *stats, const int &score) const
{
    if(stats->min > score || stats->min == -1)
        stats->min = score;
    if(stats->max < score)
        stats->max = score;
}

void DCUpdateScoreRange::setInputRangeStats(DCInput &input, DCStatsModel *playerStat) const
{
    input.min = playerStat->min;
    input.max = playerStat->max;
}
