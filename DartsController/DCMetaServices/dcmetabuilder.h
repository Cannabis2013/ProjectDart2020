#ifndef DCMETABUILDER_H
#define DCMETABUILDER_H
#include "DartsController/DCMetaSLAs/abstractdcmetabuilder.h"
class DCMetaBuilder : public AbstractDCMetaBuilder
{
public:
    DCMetaBuilder(IDCMetaCtx *metaContext, AbstractDCIdxCtrl *indexController,
                  AbstractDCScoresCtx *scoresContext, IDartsStatusCodes *statusCodes)
    {
        setMetaContext(metaContext);
        setIndexController(indexController);
        setScoresContext(scoresContext);
        setStatusCodes(statusCodes);
    }
    virtual DCMeta create() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index()->setIndex();
        meta.currentPlayerId = scoresContext()->scores().at(setIndex).playerId;
        meta.currentPlayerName = scoresContext()->scores().at(setIndex).playerName;
        return meta;
    }
    virtual DCMeta winnerMeta() const override
    {
        auto meta = metaCtx()->get();
        auto index = idxCtrl()->index();
        meta.winnerId = scoresContext()->scores().at(index->setIndex()).playerId;
        meta.winnerName = scoresContext()->scores().at(index->setIndex()).playerName;
        meta.status = statusCodes()->winnerFound();
        return meta;
    }
};
#endif // DCMETAMODELBUILDER_H
