#ifndef ABSTRACTDCTURNVALUES_H
#define ABSTRACTDCTURNVALUES_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
class AbstractDCTurnValues
{
public:
    virtual DCTurnValues turnValues() const = 0;
    const AbstractDCIdxCtrl *indexController() const
    {
        return _indexController;
    }
    void setIndexController(AbstractDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }
    const  AbstractDCScoresCtx *scoreModels() const
    {
        return _scoreModels;
    }
    void setScoreModels(AbstractDCScoresCtx *newScoreModels)
    {
        _scoreModels = newScoreModels;
    }
    const IDCFinishBuilder *logisticService() const
    {
        return _logisticService;
    }
    void setLogisticService(const IDCFinishBuilder *newLogisticService)
    {
        _logisticService = newLogisticService;
    }
private:
    const AbstractDCIdxCtrl *_indexController;
    const AbstractDCScoresCtx *_scoreModels;
    const IDCFinishBuilder *_logisticService = nullptr;
};
#endif // IBUILDTURNVALUES_H
