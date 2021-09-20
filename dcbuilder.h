#ifndef BUILDDARTSSCORECONTROLLER_H
#define BUILDDARTSSCORECONTROLLER_H

#include "DartsController/dartscontroller.h"
// Include services
#include "abstractdcbuilder.h"
#include "dsccreateinputmodels.h"

#include "idcmetainfo.h"
#include "icreatedcmetainfo.h"
#include "idcmetainfo.h"
#include "dscontroller.h"
#include "DPController/dpcontroller.h"

#include <createDCMetaInfo.h>

class DCBuilder : public AbstractDCBuilder
{
    // IControllerBuilder interface
public:
    // Public types
    enum DisplayHint
    {
        SingleColumn = 0x4,
        MultiColumn = 0x8
    };
    enum AbstractRouteByInputHint{
        PointHint = 0x5,
        ScoreHint = 0x6
    };
    virtual void createController(const QByteArray &json) override;
private:
    AbstractDartsController *createDC(const DCBuilding::IDCMetaInfo *meta);
    AbstractDartsController *createDPC(const DCBuilding::IDCMetaInfo *meta);
    AbstractDartsController *createDSC(const DCBuilding::IDCMetaInfo *meta);
    ICreateDCMetaInfo* _createMeta = new createDCMetaInfo;

};

#endif // BUILDDARTSSCORECONTROLLER_H
