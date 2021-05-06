#ifndef CONNECTDARTSSINGLESCORECONTROLLER_H
#define CONNECTDARTSSINGLESCORECONTROLLER_H

#include "qobject.h"
#include "iternaryservice.h"
#include "abstractdartsscorecontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"

#include <qobject.h>

class ConnectDartsSingleScoreController :
        public ITernaryService<AbstractDartsScoreController*,
                               AbstractApplicationInterface*,
                               AbstractModelsService*,
                               void>
{
    // ITernaryService interface
public:
    void service(AbstractDartsScoreController* controller, AbstractApplicationInterface* application, AbstractModelsService* modelsService) override;
};

#endif // CONNECTDARTSSINGLESCORECONTROLLER_H
