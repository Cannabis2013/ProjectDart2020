#include "updateplayerstats.h"
#include "SLAs/servicescontext.h"
#include <qvector.h>
#include "Players/Models/currentstats.h"
#include "Inputs/Models/input.h"

UpdatePlayerStats::UpdatePlayerStats(ServicesContext *provider)
{
    _statsDb = provider->currentStatsServices()->statsDb();
    _calcAvg = provider->statsServices()->calcAverage();
    _updateScoreRange = provider->statsServices()->updateScoreRange();
}

void UpdatePlayerStats::update(Ipt &input)
{
    upd(input);
}

void UpdatePlayerStats::update(Ipts &inputs)
{
    for (auto &input : inputs)
        upd(input);
}


void UpdatePlayerStats::upd(Ipt &input)
{
    auto ipt = input;
    auto stats = &_statsDb->model([=](const CurrentStats& m){return m.name == input.name;});
    updateAccumulatedScore(input,stats);
    stats->mid = _calcAvg->middleValue(stats->accScore,stats->n);
    _updateScoreRange->update(ipt,stats);
    ipt.stats = *stats;
}

void UpdatePlayerStats::updateAccumulatedScore(const Ipt &input, CurrentStats *stats)
{

    auto currentScore = stats->accScore;
    auto inputScore = input.score;
    auto newScore = currentScore + inputScore;
    stats->accScore = newScore;
    stats->n += 1;
}
