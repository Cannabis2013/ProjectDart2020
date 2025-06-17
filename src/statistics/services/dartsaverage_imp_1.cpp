#include "statscalculator.h"

#ifdef USE_IMP_1
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

int multiplier(const QString& mod){
    if(mod == "S")
        return 1;
    else if(mod == "D")
        return 2;
    else if(mod == "T")
        return 3;
    else
        return -1;
}

int accumulated(const QList<DartsInput> &inputs){
    auto result = 0;
    auto tempPoint = 0;
    QString tempMod;
    for (const auto &input : inputs) {
        tempPoint = input.point();
        tempMod = input.mod();
        int mult = multiplier(tempMod);
        result += tempPoint*mult;
    }
    return result;
}

double StatsCalculator::middle(const QString& name) const
{
    auto playerIndex = _services->playerFetcher->indexOf(name);
    auto inputs = _services->inputsFilter->valids(name);
    auto rounds = finishedRounds(playerIndex);
    auto score = accumulated(inputs);
    return score / rounds;
}

int StatsCalculator::finishedRounds(const int& playerIndex) const
{
    auto index = _services->indexes->index();
    auto turnIndex = index.playerIndex();
    auto rounds = index.roundIndex();
    if (rounds > 1 && playerIndex >= turnIndex)
        rounds--;
    return rounds;
}

int StatsCalculator::playerScore(const QString&) const
{
    return -1;
}

#endif
