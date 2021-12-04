#ifndef ABSTRACTDCINPUTEVALUATOR_H
#define ABSTRACTDCINPUTEVALUATOR_H
#include <qobject.h>
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/ControllerSLA/abstractdartsctrl.h"
#include "dcinput.h"
class AbstractDCInputEvaluator : public QObject
{
    Q_OBJECT
public:
    AbstractDCInputEvaluator(IDCMetaContext *metaInfo, AbsDCPlayersCtx *plaScoresCtx):
        _metaInfo(metaInfo),_plaScoresCtx(plaScoresCtx){}
    virtual void evaluate(DCInput &input, const int &scoreCand) = 0;
    IDCMetaContext *metaInfo() const {return _metaInfo;}
    AbsDCPlayersCtx *plaScoresCtx() const {return _plaScoresCtx;}
private:
    IDCMetaContext *_metaInfo;
    AbsDCPlayersCtx *_plaScoresCtx;
};
#endif // IPOINTVALIDATOR_H
