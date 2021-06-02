#include "dartssingleattemptindexesbuilder.h"
using namespace DartsModelsContext;

const IDartsPointIndexes *DartsSingleAttemptIndexesBuilder::buildIndexes(const QVector<const IModel<QUuid,QByteArray> *> &orderedModels,
                                                                         const int &assignedPlayersCount, const int &totalInputModelsCount,
                                                                         const int &numberOfAttempts) const
{
    if(!orderedModels.isEmpty())
        return assembleDartsIndexesByModels(orderedModels,assignedPlayersCount,totalInputModelsCount,numberOfAttempts);
    return assembleInitialDartsIndexes();
}

const IDartsPointIndexes *DartsSingleAttemptIndexesBuilder::assembleDartsIndexesByModels(const QVector<const IModel<QUuid,QByteArray> *> &orderedModels,
                                                                                         const int& totalInputModelsCount,
                                                                                         const int &assignedPlayersCount,
                                                                                         const int &attempts) const
{
    auto indexes = DartsPointIndexes::createInstance();
    auto lastModel = dynamic_cast<const IDartsPointInput*>(orderedModels.last());
    auto totalTurns = totalInputModelsCount;
    auto turnIndex = orderedModels.count();
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

