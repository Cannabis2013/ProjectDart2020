#ifndef BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H
#define BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H

#include "imodelsservicebuilder.h"
#include "dartspointmodelsservice.h"
#include "dartsinputsfilterservice.h"
#include "dartssingleattemptindexesbuilder.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "dartsinputmodelhintservice.h"
#include "dartspointjsondbservice.h"
#include "assembledartspointsfromjson.h"
#include "assemblejsonarrayfromdartspoints.h"
#include "idartspointdb.h"
namespace DartsModelsContext {
    class BuildDartsPointServiceWithLocalJsonDb : public IModelsServiceBuilder<IDartsPointModelsService<IDartsPointDb>>
    {
    public:
        ServiceInterface *buildModelsService() const override;
    };
}


#endif // BUILDDARTSPOINTSERVICEWITHLOCALJSONDB_H
