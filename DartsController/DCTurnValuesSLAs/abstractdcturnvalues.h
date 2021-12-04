#ifndef ABSTRACTDCTURNVALUES_H
#define ABSTRACTDCTURNVALUES_H
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
class AbstractDCTurnValues
{
public:
    virtual DCTurnValues turnValues() const = 0;
    const AbsDCIdxCtrl *indexController() const
    {
        return _indexController;
    }
    void setIndexController(AbsDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }
    const  AbsDCPlayersCtx *scoreModels() const
    {
        return _scoreModels;
    }
    void setScoreModels(AbsDCPlayersCtx *newScoreModels)
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
    const AbsDCIdxCtrl *_indexController;
    const AbsDCPlayersCtx *_scoreModels;
    const IDCFinishBuilder *_logisticService = nullptr;
};
#endif // IBUILDTURNVALUES_H
