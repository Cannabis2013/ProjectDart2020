#ifndef ABSDCCALCSCORE_H
#define ABSDCCALCSCORE_H
#include "absdcplayersctx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
class AbsDCCalcScore
{
public:
    AbsDCCalcScore(IDCIdxCtrl *indexController, AbsDCPlayersCtx *scoresContext):
        _idxCtrl(indexController),_scoresContext(scoresContext){}
    virtual int calc(DCInput &input) const = 0;
    virtual int calc(const int &scoreCandidate) const = 0;
    AbsDCPlayersCtx *scoresContext() const {return _scoresContext;}
    IDCIdxCtrl *idxCtrl() const {return _idxCtrl;}
private:
    IDCIdxCtrl *_idxCtrl;
    AbsDCPlayersCtx *_scoresContext;
};
#endif // ABSDCCALCSCORE_H
