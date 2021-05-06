#ifndef CONNECTCONTROLLERBUILDER_H
#define CONNECTCONTROLLERBUILDER_H

#include "iternaryservice.h"
#include "AbstractApplicationInterface.h"
#include "abstractdartscontrollerbuilder.h"
#include "abstractmodelsservice.h"

#include <qobject.h>

class ConnectControllerBuilder :
        public ITernaryService<AbstractApplicationInterface*,
                              AbstractDartsControllerBuilder*,
                              AbstractModelsService*,void>
{
public:


    // IBinaryService interface
public:
    void service(AbstractApplicationInterface* application,
                 AbstractDartsControllerBuilder* controllerBuilder,
                 AbstractModelsService* modelsService) override;
};

#endif // CONNECTCONTROLLERBUILDER_H
