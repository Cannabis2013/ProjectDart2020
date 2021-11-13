#ifndef ABSTRACTDCINPUTEVALUATOR_H
#define ABSTRACTDCINPUTEVALUATOR_H
#include <qobject.h>
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
class AbstractDCInputEvaluator : public QObject
{
    Q_OBJECT
public:
    virtual void evaluate(AbstractDartsInput *input, const int &scoreCand,IDCMetaInfo *metaInfo ,AbstractDartsController *controller,
                          const IDartsStatusCodes *statusCodes,IDCPlayerController *playerController = nullptr) = 0;
};


#endif // IPOINTVALIDATOR_H
