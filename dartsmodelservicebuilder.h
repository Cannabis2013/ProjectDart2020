#ifndef DARTSTOURNAMNETMODELSERVICEBUILDER_H
#define DARTSTOURNAMNETMODELSERVICEBUILDER_H

#include "dartsmodelsservice.h"
#include "assembledartstournamentmodelfromjson.h"
#include "getordereddartspointmodels.h"
#include "imodelsservicebuilder.h"
#include "tournamentjsondb.h"
#include "dartspointdbservice.h"
#include "assembledartspointindexesbydartspointmodel.h"

class DartsModelServiceBuilder :
        public IModelsServiceBuilder<IDartsModelsService>
{

    // IDartsServiceBuilder interface
public:
    IDartsModelsService *buildModelsService() const override;
};



#endif // DARTSTOURNAMNETMODELSERVICEBUILDER_H
