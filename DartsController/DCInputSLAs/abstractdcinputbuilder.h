#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include <qjsonarray.h>
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
#include "dciptvals.h"
class AbstractDCInputBuilder
{
public:
    typedef AbstractDCIdxCtrl IndexCtrl;
    typedef AbstractDCScoresCtx ScoresCtx;
    typedef IDCPlayerCtx PlayersCtx;
    virtual DCIptVals create(const QByteArray &json) const = 0;
protected:
    IDCMetaCtx *metaCtx() const
    {
        return _metaContext;
    }
    void setMetaCtx(IDCMetaCtx *newMetaContext)
    {
        _metaContext = newMetaContext;
    }
    IDCCalcScore *inputScoreCtx() const
    {
        return _inputScoreContext;
    }
    void setInputScoreCtx(IDCCalcScore *newInputScoreContext)
    {
        _inputScoreContext = newInputScoreContext;
    }
    IndexCtrl *indexCtrl() const
    {
        return _indexCtrl;
    }
    void setIndexCtrl(IndexCtrl *newIndexCtrl)
    {
        _indexCtrl = newIndexCtrl;
    }
    ScoresCtx *scoresCtx() const
    {
        return _scoresContext;
    }
    void setScoresCtx(ScoresCtx *newScoresContext)
    {
        _scoresContext = newScoresContext;
    }
    PlayersCtx *playersContext() const
    {
        return _playersContext;
    }
    void setPlayersCtx(PlayersCtx *newPlayersContext)
    {
        _playersContext = newPlayersContext;
    }
private:
    IDCMetaCtx *_metaContext;
    IDCCalcScore *_inputScoreContext;
    IndexCtrl *_indexCtrl;
    ScoresCtx *_scoresContext;
    PlayersCtx *_playersContext;
};
#endif // IDPCMODELCREATOR_H
