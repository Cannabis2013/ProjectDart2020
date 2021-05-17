#ifndef CONNECTDARTSPOINTCONTROLLER_H
#define CONNECTDARTSPOINTCONTROLLER_H

#include "qobject.h"
#include "iternaryservice.h"
#include "abstractdartspointcontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"


class ConnectDartsSingleAttemptPointController :
        public ITernaryService<AbstractDartsPointController*,
                               AbstractApplicationInterface*,
                               AbstractModelsService*,
                               AbstractDartsPointController*>
{
public:
    AbstractDartsPointController *service(AbstractDartsPointController* controller,
                                         AbstractApplicationInterface* application,
                                         AbstractModelsService* modelsService) override;
};

#endif // CONNECTDARTSPOINTCONTROLLER_H
