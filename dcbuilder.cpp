#include "dcbuilder.h"

void DCBuilder::createController(const QByteArray &json)
{
    auto meta = _createMeta->service(json);
    auto controller = createDC(meta);
    emit sendController(controller);
}

AbstractDartsController *DCBuilder::createDC(const DartsBuilderContext::IDCMetaInfo *meta)
{
    if(meta->inputHint() == PointHint)
        return createDPC(meta);
    else if(meta->inputHint() == ScoreHint)
        return createDSC(meta);
    else
        throw "Illegal input hint";
}

AbstractDartsController *DCBuilder::createDPC(const DartsBuilderContext::IDCMetaInfo *meta)
{
    return new DPController(meta);
}

AbstractDartsController *DCBuilder::createDSC(const DartsBuilderContext::IDCMetaInfo *meta)
{
    return new DSController(meta);
}
