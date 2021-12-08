#ifndef DCMETABUILDER_H
#define DCMETABUILDER_H
#include "DartsController/DCMetaSLAs/abstractdcmetabuilder.h"
class DCMetaBuilder : public AbstractDCMetaBuilder
{
public:
    DCMetaBuilder(IDCMetaContext *metaContext, IDCIdxCtrl *indexController,
                  AbsDCPlayersCtx *scoresContext)
        :AbstractDCMetaBuilder(metaContext,indexController,scoresContext){}
    virtual DCMeta create() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index().setIndex;
        meta.playerName = scoresContext()->players().at(setIndex).name;
        return meta;
    }
    virtual DCMeta winnerMeta() const override
    {
        auto meta = metaCtx()->get();
        auto setIndex = idxCtrl()->index().setIndex;
        meta.winnerName = scoresContext()->players().at(setIndex).name;
        meta.status = metaCtx()->WinnerDeclared;
        return meta;
    }
};
#endif // DCMETAMODELBUILDER_H
