#ifndef DCBUILDER_H
#define DCBUILDER_H

#include "DartsController/Controller/dartscontroller.h"
// Include services
#include "DartsControllerBuilder/SLAs/abstractdcbuilder.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include "DartsController/DartsScoreController/dscontroller.h"
#include "DartsController/DPController/dpcontroller.h"
#include "DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h"

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
