#include "dccreateturnvalues.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include <Models/dcturnvalues.h>

DCCreateTurnValues::DCCreateTurnValues(DCServices *services)
{
    _indexController = services->indexServices()->indexController();
    _playerManager = services->playerServices()->playerManager();
    _createFinishes = services->finServices()->finishBuilder();
}

DCTurnValues DCCreateTurnValues::create() const
{
    auto index = _indexController->index();
    auto player = _playerManager->player(index.playerIndex);
    auto finish = _createFinishes->suggestTargetRow(player.remScore,index.attemptIndex);
    return turnValues(index,player,finish);
}

DCTurnValues DCCreateTurnValues::turnValues(const DCIndex &index, const DCPlayer &player, const QString &finish) const
{
    DCTurnValues model;
    model.canUndo = index.turnIndex > 0;
    model.canRedo = index.turnIndex < index.totalTurns;
    model.roundIndex = index.roundIndex;
    model.setIndex = index.playerIndex;
    model.attemptIndex = index.attemptIndex;
    model.targetRow = finish;
    model.playerName = player.name;
    return model;
}
