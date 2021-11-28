#ifndef ABSTRACTDCINPUTEVALUATOR_H
#define ABSTRACTDCINPUTEVALUATOR_H
#include <qobject.h>
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcmetactx.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
#include "DartsController/ControllerSLA/abstractdartsctrl.h"
#include "dciptvals.h"
class AbstractDCInputEvaluator : public QObject
{
    Q_OBJECT
public:
    virtual void evaluate(DCIptVals &input, const int &scoreCand,IDCMetaCtx *metaInfo ,AbstractDartsCtrl *controller,
                          const IDartsStatusCodes *statusCodes,IDCPlayerCtx *playerController = nullptr) = 0;
};


#endif // IPOINTVALIDATOR_H
