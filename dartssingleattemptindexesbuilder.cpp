#include "dartssingleattemptindexesbuilder.h"
using namespace DartsModelsContext;

const IDartsPointIndexes *DartsSingleAttemptIndexesBuilder::buildIndexes(const QVector<const IDartsInput *> &orderedModels, const int &assignedPlayersCount, const int &numberOfAttempts) const
{
    if(!orderedModels.isEmpty())
        return assembleDartsIndexesByModels(orderedModels,assignedPlayersCount,numberOfAttempts);
    return assembleInitialDartsIndexes();
}

const IDartsPointIndexes *DartsSingleAttemptIndexesBuilder::assembleDartsIndexesByModels(const QVector<const IDartsInput *> &orderedModels, const int &assignedPlayersCount, const int &attempts) const
{
    auto indexes = DartsPointIndexes::createInstance();
    auto lastModel = dynamic_cast<const IDartsPointInput*>(orderedModels.last());
    auto totalTurns = orderedModels.count();
    auto turnIndex = assignedPlayersCount;
    auto roundIndex = lastModel->roundIndex();
    auto attemptIndex = lastModel->attempt();
    auto setIndex = lastModel->setIndex();
    if(++attemptIndex % attempts == 0)
    {
        attemptIndex = 0;
        setIndex++;
        if(setIndex >= assignedPlayersCount)
        {
            roundIndex++;
            setIndex = 0;
        }
    }
    indexes->setTotalTurns(totalTurns);
    indexes->setTurnIndex(turnIndex);
    indexes->setRoundIndex(roundIndex);
    indexes->setSetIndex(setIndex);
    indexes->setAttemptIndex(attemptIndex);
    return indexes;
}

const IDartsPointIndexes *DartsSingleAttemptIndexesBuilder::assembleInitialDartsIndexes() const
{
    return DartsPointIndexes::createInitialInstance();
}

