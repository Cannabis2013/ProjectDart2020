#ifndef ABSTRACTEVALUATEDCINPUT_H
#define ABSTRACTEVALUATEDCINPUT_H

#include "IDCInputKeyCodes.h"
#include <qobject.h>
#include "idcinput.h"
#include "idcinput.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerApproval.h"
class AbstractEvaluateDCInput : public QObject
{
    Q_OBJECT
public:
    virtual void validateInput(const int &currentScore, const IDCInputKeyCodes *keyCodes,
                               IDCInput *input, IDCPlayerApproval *allowancesContext) = 0;
signals:
    void playerNotAllowedEntrance(IDCInput *input);
    void playerHitPointDomain(IDCInput *input);
    void playerHitTargetDomain(IDCInput *input);
    void playerOutOfRange(IDCInput *input);
};


#endif // IPOINTVALIDATOR_H
