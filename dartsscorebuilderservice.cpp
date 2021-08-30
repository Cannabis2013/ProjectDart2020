#include "dartsscorebuilderservice.h"

using namespace DartsBuilderContext;

DartsScoreBuilderService *DartsBuilderContext::DartsScoreBuilderService::createInstance()
{
    return new DartsScoreBuilderService;
}


AbstractGameController *DartsScoreBuilderService::buildDartsController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    AbstractDartsScoreController* controller = new DefaultDSController(entity);
    emit sendController(controller,entity->displayHint());
    return controller;
}

DartsScoreBuilderService *DartsScoreBuilderService::setBuildEntityByJson(ICreateDCMetaInfo *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}
