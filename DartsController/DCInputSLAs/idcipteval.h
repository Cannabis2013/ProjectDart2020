#ifndef IDCIPTEVAL_H
#define IDCIPTEVAL_H
#include <qobject.h>
#include "DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h"
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/ControllerSLA/absdartsctrl.h"
#include "dcinput.h"
class IDCIptEval : public QObject
{
    Q_OBJECT
public:
    virtual void eval(DCInput &input, const int &scoreCand, DCMeta &meta, const DCPlayer &player, const int &winnerStatus) = 0;
};
#endif // IPOINTVALIDATOR_H
