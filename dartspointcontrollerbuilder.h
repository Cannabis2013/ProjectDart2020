#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "dscontroller.h"
// Include services
#include "abstractdartscontrollerbuilder.h"
#include "dartsscoremodelsbuilder.h"
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "iternaryservice.h"
#include "dartsplayermodelbuilderservice.h"
#include "idcmetainfo.h"
#include "defaultdpcontroller.h"
#include "icreatedcmetainfo.h"

namespace DartsBuilderContext {
    class DartsPointControllerBuilder : public AbstractDartsControllerBuilder
    {
        // IControllerBuilder interface
    public:
        static DartsPointControllerBuilder *createInstance();
        AbstractGameController *buildDartsController(const QByteArray& json) override;
        DartsPointControllerBuilder *setDCMetaInfoCreator(ICreateDCMetaInfo *newBuildEntityByJson);
    private:
        ICreateDCMetaInfo* _createDCMetaInfo;
    };
}

#endif // GAMEBUILDER_H
