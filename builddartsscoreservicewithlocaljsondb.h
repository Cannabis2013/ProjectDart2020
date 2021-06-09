#ifndef LOCALJSONDBDARTSSCORESERVICEBUILDER_H
#define LOCALJSONDBDARTSSCORESERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "dartsscoremodelsservice.h"
#include "getdartsscoreindexesbymodel.h"
#include "dartsscorelessthanpredicate.h"
#include "dartsinputsfilterservice.h"
#include "inputmodelssortservice.h"
#include "dartsinputmodelhintservice.h"
#include "assemblemultiattemptscoresbyjson.h"
#include "assemblejsonbydartsscoremodels.h"

namespace DartsModelsContext {
    class BuildDartsScoreServiceWithLocalJsonDb : public
            IModelsServiceBuilder<IDartsScoreModelsService<IDartsScoreDb>>
    {
    public:
        ServiceInterface *buildModelsService() const override;
    };
}

#endif // LOCALJSONDBDARTSSCORESERVICEBUILDER_H
