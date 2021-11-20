#ifndef IDCSETINPUTSTATS_H
#define IDCSETINPUTSTATS_H
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
#include "idccalcmidval.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDCSetInputStats
{
public:
    virtual void set(AbstractDartsInput *input) const = 0;
    IDCStatsContext *statsContext() const
    {
        return _statsContext;
    }
    void setStatsContext(IDCStatsContext *newStatsContext)
    {
        _statsContext = newStatsContext;
    }
    IDCCalcMidVal *calcMidVal() const
    {
        return _calcMidVal;
    }
    void setCalcMidVal(IDCCalcMidVal *newCalcMidVal)
    {
        _calcMidVal = newCalcMidVal;
    }
    AbstractDCIdxCtrl *indexCtrl() const
    {
        return _indexCtrl;
    }
    void setIndexCtrl(AbstractDCIdxCtrl *newIndexCtrl)
    {
        _indexCtrl = newIndexCtrl;
    }
    IDCMetaCtx *metaContext() const
    {
        return _metaContext;
    }
    void setMetaContext(IDCMetaCtx *newMetaContext)
    {
        _metaContext = newMetaContext;
    }
private:
    IDCStatsContext *_statsContext;
    IDCCalcMidVal *_calcMidVal;
    AbstractDCIdxCtrl *_indexCtrl;
    IDCMetaCtx *_metaContext;
};
#endif // IDCDETSCORERANGE_H
