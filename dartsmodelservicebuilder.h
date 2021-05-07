#ifndef DARTSTOURNAMNETMODELSERVICEBUILDER_H
#define DARTSTOURNAMNETMODELSERVICEBUILDER_H

#include "dartsmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "getordereddartspointmodels.h"
#include "tournamentjsondb.h"
#include "dartspointdbservice.h"
#include "assembledartspointindexesbydartspointmodel.h"
#include "assemblesingleattemptpointsfromjson.h"
#include "assemblejsonarrayfromdartspoints.h"

class DartsModelServiceBuilder :
        public IModelsServiceBuilder<IDartsModelsService>
{

    // IDartsServiceBuilder interface
public:
    IDartsModelsService *buildModelsService() const override;
};



#endif // DARTSTOURNAMNETMODELSERVICEBUILDER_H
