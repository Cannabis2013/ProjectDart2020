#include "updatestatsmirror.h"
#include "SLAs/servicescontext.h"
#include <qvector.h>
#include "Players/Models/imirrorsdb.h"
#include "Inputs/Models/snapshot.h"

UpdateStatsMirror::UpdateStatsMirror(ServicesContext *provider)
{
    _statsDb = provider->statisticServices()->statModels();
    _calcAvg = provider->statsServices()->calcAverage();
    _updateScoreRange = provider->statsServices()->updateScoreRange();
}

void UpdateStatsMirror::update(Ipt &input)
{
    upd(input);
}

void UpdateStatsMirror::update(Ipts &inputs)
{
    for (auto &input : inputs)
        upd(input);
}

void UpdateStatsMirror::upd(Ipt &input)
{
    auto ipt = input;
    auto stats = &_statsDb->model([=](const CurrentStat& m){return m.name == input.name;});
    updateAccumulatedScore(input,stats);
    stats->mid = _calcAvg->middleValue(stats->accScore,stats->n);
    _updateScoreRange->update(ipt,stats);
    ipt.stats = *stats;
}

void UpdateStatsMirror::updateAccumulatedScore(const Ipt &input, CurrentStat*stats)
{
    auto currentScore = stats->accScore;
    auto inputScore = input.score;
    auto newScore = currentScore + inputScore;
    stats->accScore = newScore;
    stats->n += 1;
}
