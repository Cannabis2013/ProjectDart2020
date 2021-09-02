#ifndef BUILDDARTSSCORECONTROLLER_H
#define BUILDDARTSSCORECONTROLLER_H

#include "dartscontroller.h"
// Include services
#include "abstractdcbuilder.h"
#include "dsccreateinputmodels.h"
#include "iternaryservice.h"
#include "dartsplayermodelbuilderservice.h"
#include "idcmetainfo.h"
#include "icreatedcmetainfo.h"
#include "idcmetainfo.h"
#include "dscontroller.h"
#include "dpcontroller.h"

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
    static DCBuilder *createInstance();
    void buildScoreBasedController(const QByteArray &json) override;
    void buildPointBasedController(const QByteArray& json) override;
    DCBuilder *setBuildEntityByJson(ICreateDCMetaInfo *newBuildEntityByJson);
private:
    ICreateDCMetaInfo* _buildEntityByJson;
};

#endif // BUILDDARTSSCORECONTROLLER_H
