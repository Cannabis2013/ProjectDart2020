#ifndef DCPLAYERSERVICE_H
#define DCPLAYERSERVICE_H

#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
class DCPlayerService : public IDCPlayerService
{
public:
    QString currentPlayerName(const IDCIndexController *indexContext, IDCScoresService *scoresContext) const override
    {
        auto setIndex = indexContext->setIndex();
        return scoresContext->scoreModels().at(setIndex).playerName;
    }
    QUuid currentPlayerId(const IDCIndexController *indexContext, IDCScoresService *scoresContext) const override
    {
        auto setIndex = indexContext->setIndex();
        return scoresContext->scoreModels().at(setIndex).playerId;
    }
};
#endif // DCPLAYERSERVICE_H
