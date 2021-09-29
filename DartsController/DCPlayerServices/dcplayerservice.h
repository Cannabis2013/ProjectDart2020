#ifndef DCPLAYERSERVICE_H
#define DCPLAYERSERVICE_H

#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
class DCPlayerService : public IDCPlayerService
{
public:
    DCPlayerService(IDCIndexService *indexService, IDCScoresService *scoresService):
        _indexService(indexService),_scoresService(scoresService)
    {}
    QString currentPlayerName() const override
    {
        auto setIndex = _indexService->setIndex();
        return _scoresService->scoreModels().at(setIndex).playerName;
    }
    QUuid currentPlayerId() const override
    {
        auto setIndex = _indexService->setIndex();
        return _scoresService->scoreModels().at(setIndex).playerId;
    }
private:
    IDCIndexService *_indexService;
    IDCScoresService *_scoresService;
};
#endif // DCPLAYERSERVICE_H
