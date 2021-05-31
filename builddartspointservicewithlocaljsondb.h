#ifndef BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H
#define BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H

#include "imodelsservicebuilder.h"
#include "dartspointmodelsservice.h"
#include "dartsinputsfilterservice.h"
#include "dartssingleattemptindexesbuilder.h"
#include "sortplayerinputsbypredicate.h"
#include "dartspointlessthanpredicate.h"
#include "getdartsinputmodelbyid.h"
#include "removemodelsfromdbcontext.h"
#include "dartsinputmodelhintservice.h"
#include "dartspointjsondbservice.h"
namespace DartsModelsContext {
    class BuildDartsPointServiceWithLocalJsonDb : public IModelsServiceBuilder<IDartsPointModelsService>
    {
    public:
        ServiceInterface *buildModelsService() const override;
    };
}


#endif // BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H
