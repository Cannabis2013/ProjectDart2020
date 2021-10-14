#ifndef ABSTRACTEVALUATEDCINPUT_H
#define ABSTRACTEVALUATEDCINPUT_H

#include "IDCInputKeyCodes.h"
#include <qobject.h>
#include "idcinputmodel.h"
#include "idcinputmodel.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerAllowancesContext.h"
class AbstractEvaluateDCInput : public QObject
{
    Q_OBJECT
public:
    virtual void validateInput(const int &currentScore, const IDCInputKeyCodes *keyCodes,
                               DCContext::IDCInputModel *input, IDCPlayerAllowancesContext *allowancesContext) = 0;
signals:
    void playerNotAllowedEntrance(DCContext::IDCInputModel *input);
    void playerHitPointDomain(DCContext::IDCInputModel *input);
    void playerHitTargetDomain(DCContext::IDCInputModel *input);
    void playerOutOfRange(DCContext::IDCInputModel *input);
};


#endif // IPOINTVALIDATOR_H
