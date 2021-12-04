#ifndef ABSTRACTDCMETABUILDER_H
#define ABSTRACTDCMETABUILDER_H
#include "idcmetacontext.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
class AbstractDCMetaBuilder
{
public:
    AbstractDCMetaBuilder(IDCMetaContext *metaContext, AbsDCIdxCtrl *indexController,
                          AbsDCPlayersCtx *scoresContext):
    _metaInfo(metaContext),_indexController(indexController),_scoreModels(scoresContext){}
    virtual DCMeta create() const = 0;
    virtual DCMeta winnerMeta() const = 0;
    IDCMetaContext *metaCtx() const {return _metaInfo;}
    AbsDCIdxCtrl *idxCtrl() const {return _indexController;}
    AbsDCPlayersCtx *scoresContext() const {return _scoreModels;}
private:
    IDCMetaContext *_metaInfo;
    AbsDCIdxCtrl *_indexController;
    AbsDCPlayersCtx *_scoreModels;
};
#endif // IDCBUILDMETAMODEL_H
