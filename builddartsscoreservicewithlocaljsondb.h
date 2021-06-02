#ifndef LOCALJSONDBDARTSSCORESERVICEBUILDER_H
#define LOCALJSONDBDARTSSCORESERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "dartsscoremodelsservice.h"
#include "getdartsscoreindexesbymodel.h"
#include "dartsscorelessthanpredicate.h"
#include "dartsinputsfilterservice.h"
#include "removemodelsfromdbcontext.h"
#include "sortplayerinputsbypredicate.h"
#include "dartsinputmodelhintservice.h"
#include "dartsscorejsondb.h"
#include "getdartsinputmodelbyid.h"
#include "assemblemultiattemptscoresbyjson.h"
#include "assemblejsonbydartsscoremodels.h"

class BuildDartsScoreServiceWithLocalJsonDb : public
        IModelsServiceBuilder<DartsModelsContext::IDartsScoreModelsService>
{
public:
    ServiceInterface *buildModelsService() const override;
};

#endif // LOCALJSONDBDARTSSCORESERVICEBUILDER_H
