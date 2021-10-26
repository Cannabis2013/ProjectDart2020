#ifndef DCPLAYERSERVICE_H
#define DCPLAYERSERVICE_H

#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
class DCPlayerService : public IDCPlayerService
{
public:
    QString currentPlayerName(IDCIndexController *indexContoller, IDCScoreModels *scoresContext) const override
    {
        auto setIndex = indexContoller->index().setIndex;
        return scoresContext->scores().at(setIndex).playerName;
    }
    QUuid currentPlayerId(IDCIndexController *indexContoller, IDCScoreModels *scoresContext) const override
    {
        auto setIndex = indexContoller->index().setIndex;
        return scoresContext->scores().at(setIndex).playerId;
    }
};
#endif // DCPLAYERSERVICE_H
