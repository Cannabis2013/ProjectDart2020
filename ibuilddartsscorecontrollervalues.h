#ifndef IBUILDDARTSSCORECONTROLLERVALUES_H
#define IBUILDDARTSSCORECONTROLLERVALUES_H

#include "ibuildcontrollerturnvalues.h"
#include "dartsscoreturnvalues.h"
#include "idartsscoreindexservice.h"
#include "iplayerscoreservice.h"
#include "idartscontrollerscore.h"
#include "idartsinputsuggestion.h"
#include "idartsscorecontrollerindexes.h"
#include "idartsplayer.h"

namespace DartsScoreControllerContext
{
    namespace BuildDartsControllerValues
    {
        typedef IDartsPlayer<QUuid,QString> DartsPlayer;
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ScoreModel;
        typedef IDartsScoreIndexService<IDartsScoreControllerIndexes<QByteArray>> IndexService;
        typedef IPlayerScoreService<DartsPlayer,ScoreModel> PlayerInputService;
        typedef IDartsInputSuggestion<QString> LogisticService;
    }
    class IBuildDartsScoreControllerValues : public
            IBuildControllerTurnValues<DartsScoreTurnValues,
                                       BuildDartsControllerValues::IndexService,
                                       BuildDartsControllerValues::PlayerInputService,
                                       BuildDartsControllerValues::LogisticService>
    {
    public:
        virtual const Model *createTurnValues(const IndexService *indexService,
                                                        const InputService *playerScoreService,
                                                        const LogisticService *logisticService) const = 0;
    };
}

#endif // IBUILDDARTSSCORECONTROLLERVALUES_H
