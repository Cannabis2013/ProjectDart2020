#ifndef ABSTRACTDCMETABUILDER_H
#define ABSTRACTDCMETABUILDER_H
#include "idartsstatuscodes.h"
#include "idcmetactx.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
class AbstractDCMetaBuilder
{
public:
    virtual DCMeta create() const = 0;
    virtual DCMeta winnerMeta() const = 0;
    IDCMetaCtx *metaCtx() const
    {
        return _metaInfo;
    }
    void setMetaContext(IDCMetaCtx *newMetaInfo)
    {
        _metaInfo = newMetaInfo;
    }
    AbstractDCIdxCtrl *idxCtrl() const
    {
        return _indexController;
    }
    void setIndexController(AbstractDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }

    AbstractDCScoresCtx *scoresContext() const
    {
        return _scoreModels;
    }
    void setScoresContext(AbstractDCScoresCtx *newScoreModels)
    {
        _scoreModels = newScoreModels;
    }
    IDartsStatusCodes *statusCodes() const
    {
        return _statusCodes;
    }
    void setStatusCodes(IDartsStatusCodes *statusCodes)
    {
        _statusCodes = statusCodes;
    }
private:
    IDCMetaCtx *_metaInfo;
    AbstractDCIdxCtrl *_indexController;
    AbstractDCScoresCtx *_scoreModels;
    IDartsStatusCodes *_statusCodes;
};




#endif // IDCBUILDMETAMODEL_H
