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
    virtual void evaluateInput(const int &remainingScore, DCInput input,  IDCPlayerApproval *allowancesContext,
                               AbstractDartsController *controller) = 0;
signals:
    void playerNotAllowedEntrance(DCInput &input);
    void playerHitPointDomain(const DCInput &input);
    void playerHitTargetDomain(const DCInput &input);
    void playerOutOfRange(DCInput &input);
};


#endif // IPOINTVALIDATOR_H
