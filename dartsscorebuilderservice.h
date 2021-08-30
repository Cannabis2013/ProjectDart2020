#ifndef BUILDDARTSSCORECONTROLLER_H
#define BUILDDARTSSCORECONTROLLER_H


#include "dscontroller.h"
// Include services
#include "abstractdartscontrollerbuilder.h"
#include "dartsscoremodelsbuilder.h"
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "iternaryservice.h"
#include "dartsplayermodelbuilderservice.h"
#include "idcmetainfo.h"
#include "icreatedcmetainfo.h"
#include "idcmetainfo.h"
#include "defaultdscontroller.h"


namespace DartsBuilderContext {
    class DartsScoreBuilderService : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        // Public types
        enum DisplayHint
        {
            SingleColumn = 0x4,
            MultiColumn = 0x8
        };
        static DartsScoreBuilderService *createInstance();

        AbstractGameController *buildDartsController(const QByteArray& json) override;
        DartsScoreBuilderService *setBuildEntityByJson(ICreateDCMetaInfo *newBuildEntityByJson);
    private:
        ICreateDCMetaInfo* _buildEntityByJson;
    };
}

#endif // BUILDDARTSSCORECONTROLLER_H
