#include "dcbuilder.h"

using namespace DartsBuilderContext;

DCBuilder *DCBuilder::createInstance()
{
    return new DCBuilder;
}

void DCBuilder::buildScoreBasedController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    auto controller = new DPController(entity);
    emit sendController(controller,entity->displayHint());
}

void DCBuilder::buildPointBasedController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    auto controller = new DSController(entity);
    emit sendController(controller,entity->displayHint());
}

DCBuilder *DCBuilder::setBuildEntityByJson(ICreateDCMetaInfo *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}
