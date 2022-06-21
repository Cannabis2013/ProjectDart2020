#include "updatecurrentstats.h"
#include <qvector.h>
#include <DartsStatistics/Contracts/SLAs/servicescontext.h>
#include <DartsStatistics/Contracts/Db/istatsdb.h>

UpdateCurrentStats::UpdateCurrentStats(ServicesContext *provider)
{
        _statsDb = provider->statisticServices()->statModels();
        _calcAvg = provider->statsServices()->calcAverage();
        _updateScoreRange = provider->statsServices()->updateScoreRange();
}

void UpdateCurrentStats::update(Ipt &input)
{
        upd(input);
}

void UpdateCurrentStats::update(Inputs &inputs)
{
        for (auto &input : inputs)
                upd(input);
}

void UpdateCurrentStats::upd(Ipt &input)
{
        auto ipt = input;
        auto stats = &_statsDb->model([=](const CurrentStat& m){return m.name == input.name;});
        updateAccumulatedScore(input,stats);
        stats->mid = _calcAvg->middleValue(stats->accScore,stats->n);
        _updateScoreRange->update(ipt,stats);
        ipt.stats = *stats;
}

void UpdateCurrentStats::updateAccumulatedScore(const Ipt &input, CurrentStat*stats)
{
    stats->accScore += input.score;
    stats->n += 1;
}
