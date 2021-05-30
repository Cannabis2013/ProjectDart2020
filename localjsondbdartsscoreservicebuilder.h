#ifndef LOCALJSONDBDARTSSCORESERVICEBUILDER_H
#define LOCALJSONDBDARTSSCORESERVICEBUILDER_H

#include "imodelsservicebuilder.h"
#include "dartsscoremodelsservice.h"
#include "getdartsscoreindexesbymodel.h"
#include "dartsscorelessthanpredicate.h"
#include "dartsinputsfilterservice.h"
#include "removemodelsfromdbcontext.h"
#include "sortplayerinputsbypredicate.h"
#include "setdartsinputhintservice.h"
#include "dartsscorejsondb.h"
#include "getdartsinputmodelbyid.h"
class LocalJsonDbDartsScoreServiceBuilder : public
        IModelsServiceBuilder<DartsModelsContext::IDartsScoreModelsService>
{
public:
    ServiceInterface *buildModelsService() const override;
};

#endif // LOCALJSONDBDARTSSCORESERVICEBUILDER_H
