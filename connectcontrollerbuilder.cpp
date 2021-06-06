#include "connectcontrollerbuilder.h"

void ConnectControllerBuilder::service(AbstractApplicationInterface *application,
                                       AbstractDartsControllerBuilder *controllerBuilder,
                                       AbstractModelsService *modelsService)
{
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsDetails,
            application,&AbstractApplicationInterface::assembleAndConfigureControllerBuilder);
    QObject::connect(application,&AbstractApplicationInterface::assembleDartsController,
            controllerBuilder,&AbstractDartsControllerBuilder::assembleDartsGameController);
    QObject::connect(controllerBuilder,&AbstractDartsControllerBuilder::sendController,
            application,&AbstractApplicationInterface::setGameController);
}
