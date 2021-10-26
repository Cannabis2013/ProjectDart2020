#ifndef ABSTRACTDCINPUTEVALUATOR_H
#define ABSTRACTDCINPUTEVALUATOR_H
#include <qobject.h>
#include "DartsController/DCPlayerSLAs/IDCPlayerApproval.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
class AbstractDCInputEvaluator : public QObject
{
    Q_OBJECT
public:
    virtual void evaluateInput(DCInput input, IDCPlayerApproval *allowancesContext,
                               AbstractDartsController *controller) = 0;
};


#endif // IPOINTVALIDATOR_H
