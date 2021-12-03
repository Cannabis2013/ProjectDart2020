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
        auto setIndex = idxCtrl()->index().setIndex;
        meta.playerName = scoresContext()->scores().at(setIndex).name;
        return meta;
    }
    virtual DCMeta winnerMeta() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index().setIndex;
        meta.winnerName = scoresContext()->scores().at(setIndex).name;
        meta.status = statusCodes()->winnerFound();
        return meta;
    }
};
#endif // DCMETAMODELBUILDER_H
