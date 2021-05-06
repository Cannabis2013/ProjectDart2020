#include "connectcontrollerbuilder.h"

void ConnectControllerBuilder::service(AbstractApplicationInterface *application,
                                       AbstractDartsControllerBuilder *controllerBuilder,
                                       AbstractModelsService *modelsService)
{
    QObject::connect(application,&AbstractApplicationInterface::setCurrentActiveTournament,
            modelsService,&AbstractModelsService::handleRequestGameMode);
    QObject::connect(modelsService,&AbstractModelsService::requestAssembleTournament,
            controllerBuilder,&AbstractDartsControllerBuilder::determineTournamentGameMode);
    QObject::connect(controllerBuilder,&AbstractDartsControllerBuilder::requestDartsDetails,
            modelsService,&AbstractModelsService::assembleDartsKeyValues);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentFtpDetails,
            application,&AbstractApplicationInterface::assembleAndConfigureControllerBuilder);
    QObject::connect(application,&AbstractApplicationInterface::assembleDartsController,
            controllerBuilder,&AbstractDartsControllerBuilder::assembleDartsGameController);
    QObject::connect(controllerBuilder,&AbstractDartsControllerBuilder::sendController,
            application,&AbstractApplicationInterface::setGameController);
}
