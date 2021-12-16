#ifndef DCMETABUILDER_H
#define DCMETABUILDER_H
#include "DartsController/DCMetaSLAs/abstractdcmetabuilder.h"
#include "dcmeta.h"
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
class DCMetaBuilder : public AbstractDCMetaBuilder
{
public:
    DCMetaBuilder(IDCMetaContext *metaContext, IDCIdxCtrl *indexController,
                  AbsDCPlayersCtx *scoresContext)
        :AbstractDCMetaBuilder(metaContext,indexController,scoresContext){}
    DCMeta create() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index().setIndex;
        meta.playerName = scoresContext()->players().at(setIndex).name;
        return meta;
    }
    DCMeta create(const TnmVals &tournament) const override
    {
        DCMeta meta;
        meta.tournamentId = tournament.tournamentId;
        meta.playersCount = tournament.playerCount;
        meta.initRemScore = tournament.initRem;
        meta.winnerName = tournament.winnerName;
        meta.index.totalTurns = tournament.totalTurns;
        meta.index.turnIndex = tournament.turnIndex;
        meta.index.roundIndex = tournament.roundIndex;
        meta.index.setIndex = tournament.setIndex;
        meta.index.attemptIndex = tournament.attemptIndex;
        return meta;
    }
    DCMeta winnerMeta() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index().setIndex;
        meta.winnerName = scoresContext()->players().at(setIndex).name;
        meta.status = metaCtx()->WinnerDeclared;
        return meta;
    }
};
#endif // DCMETAMODELBUILDER_H
