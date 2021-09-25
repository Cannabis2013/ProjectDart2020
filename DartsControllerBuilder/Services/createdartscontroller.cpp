#include "createdartscontroller.h"

void CreateDartsController::createController(const QByteArray &json)
{
    auto meta = _createMeta->service(json);
    auto controller = createDC(meta);
    emit sendController(controller);
}

AbstractDartsController *CreateDartsController::createDC(const DCBuilding::IDCMetaInfo *meta)
{
    if(meta->inputHint() == PointHint)
        return createDPC(meta);
    else if(meta->inputHint() == ScoreHint)
        return createDSC(meta);
    else
        throw "Illegal input hint";
}

AbstractDartsController *CreateDartsController::createDPC(const DCBuilding::IDCMetaInfo *meta)
{
    return new DPController(meta);
}

AbstractDartsController *CreateDartsController::createDSC(const DCBuilding::IDCMetaInfo *meta)
{
    return new DSController(meta);
}
