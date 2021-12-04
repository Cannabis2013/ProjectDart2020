#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include <qjsonarray.h>
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/DCScoresSLAs/absdccalcscore.h"
#include "dcinput.h"
class AbstractDCInputBuilder
{
public:
    typedef AbsDCIdxCtrl IndexCtrl;
    typedef AbsDCPlayersCtx PlayersContext;
    virtual DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const = 0;
    virtual DCInput create(const int &remScore, const DCPlayer &player) const = 0;
protected:
    AbstractDCInputBuilder(AbsDCCalcScore *scoreCalc):
        _inputScoreContext(scoreCalc){}
    AbsDCCalcScore *inputScoreCtx() const {return _inputScoreContext;}
private:
    AbsDCCalcScore *_inputScoreContext;
};
#endif // IDPCMODELCREATOR_H
