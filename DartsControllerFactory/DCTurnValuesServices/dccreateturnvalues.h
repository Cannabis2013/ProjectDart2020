#ifndef DCCREATETURNVALUES_H
#define DCCREATETURNVALUES_H
#include "DCTurnValuesSLAs/idccreateturnvalues.h"
#include "DCTurnValuesServices/dcturnvalues.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "ServicesProvider/dcservices.h"
class DCCreateTurnValues : public IDCCreateTurnValues
{
public:
    DCCreateTurnValues(DCServices *services):_services(services){};
    DCTurnValues create() const override
    {
        auto index = _services->indexService()->index();
        auto player = _services->playerService()->player(index.playerIndex);
        auto finish = _services->finishBuilder()->suggestTargetRow(player.remScore,index.attemptIndex);
        return turnValues(index,player,finish);
    }
private:
    DCTurnValues turnValues(const DCIndex &index, const DCPlayer &player, const QString &finish) const
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
    DCServices *_services;
};
#endif // ASSEMBLEDARTSSCORETURNVALUES_H
