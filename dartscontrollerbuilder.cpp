#include "dartscontrollerbuilder.h"

using namespace DartsBuilderContext;

DartsControllerBuilder* DartsControllerBuilder::createInstance()
{
    return new DartsControllerBuilder();
}

AbstractGameController *DartsControllerBuilder::assembleDartsGameController(const QByteArray &json,
                                                                            AbstractApplicationInterface *applicationInterface,
                                                                            AbstractModelsService *modelsContext)
{
    auto entity = _buildEntityByJson->service(json);
    auto inputHint = entity->inputHint();
    if(inputHint == InputModes::PointMode)
    {
        AbstractDartsPointController* controller = _buildSingleAttemptPointController->buildSingleAttemptPointController(entity);
        _connectDartsSingleAttemptPointController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else if(inputHint == InputModes::ScoreMode)
    {
        AbstractDartsScoreController* controller = _buildMultiAttemptScoreController->buildSingleAttemptPointController(entity);
        _connectDartsScoreController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else
        throw "Invalid inputmode";
}

void DartsControllerBuilder::determineTournamentGameMode(const QUuid &tournament, const int &gameMode)
{
    if(gameMode == GameModes::FirstToPost)
        emit requestDartsDetails(tournament);
}

DartsControllerBuilder *DartsControllerBuilder::setBuildMultiAttemptScoreController(BuildMultiAttemptScoreController *newBuildMultiAttemptScoreController)
{
    _buildMultiAttemptScoreController = newBuildMultiAttemptScoreController;
    return this;
}

DartsControllerBuilder *DartsControllerBuilder::setBuildSingleAttemptPointController(BuildSingleAttemptPointController *newBuildSingleAttemptPointController)
{
    _buildSingleAttemptPointController = newBuildSingleAttemptPointController;
    return this;
}

DartsControllerBuilder *DartsControllerBuilder::setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsMultiAttemptScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, void> *connectDartsScoreController)
{
    _connectDartsScoreController = connectDartsScoreController;
    return this;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsSingleAttemptPointController(ConnectSingleAttempPointController *connectDartsPointController)
{
    _connectDartsSingleAttemptPointController = connectDartsPointController;
    return this;
}
