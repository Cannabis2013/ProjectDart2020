#include "addtotalscoretodartsinputs.h"

void DartsPointControllerContext::AddTotalScoreToDartsInputs::addTotalScoreToInputs(const InputModels &inputModels,
                                                                                    const int &initialPoint) const
{
    auto playerIds = buildListOfPlayerIds(inputModels);
    for (const auto &playerId : playerIds) {
        auto playerInputModels = getPointInputModelsByPlayerId(inputModels,playerId);
        addTotalScoreToInputs(playerInputModels,initialPoint);
    }
}

QVector<QUuid> DartsPointControllerContext::AddTotalScoreToDartsInputs::buildListOfPlayerIds(const InputModels &inputModels) const
{
    QVector<QUuid> playerIds;
    for (const auto &input : inputModels) {
        auto playerId = input->playerId();
        if(!playerIds.contains(playerId))
            playerIds << playerId;
    }
    return playerIds;
}

DartsPointControllerContext::IAddTotalScoreToDartsInputs::InputModels DartsPointControllerContext::AddTotalScoreToDartsInputs::getPointInputModelsByPlayerId(const InputModels &inputModels,
                                                                                                                                                             const QUuid &playerId) const
{
    InputModels playerInputModels;
    for (const auto &inputModel : inputModels) {
        if(inputModel->playerId() == playerId)
            playerInputModels << inputModel;
    }
    return playerInputModels;
}

void DartsPointControllerContext::AddTotalScoreToDartsInputs::addTotalScoresToInputModels(const InputModels &inputModels,
                                                                                          const int &initialScore) const
{
    auto tempScore = initialScore;
    for (const auto &inputModel : inputModels) {
        auto nonConstInputModel = const_cast<InputModel*>(inputModel);
        nonConstInputModel->setTotalScore(tempScore);
        auto inputScore = inputModel->score();
        tempScore = tempScore - inputScore;
    }
}
