#ifndef DEFAULTMODELSSERVICEBUILDER_H
#define DEFAULTMODELSSERVICEBUILDER_H

#include "abstractmodelsservicebuilder.h"
#include "abstractmodelsservice.h"
#include "localmodelsservice.h"
#include "getplayerindexesfromjson.h"
#include "assemblejsonfromdartspointindexes.h"
#include "jsonarrayfromplayernamesandids.h"
#include "assemblejsonfromdartspoints.h"
#include "assemblejsonfromordereddartspointmodels.h"
#include "assembledartstournamentmodelfromjson.h"
#include "assemblejsonbasictournamentvaluesfrommodel.h"
#include "assemblejsondartstournamentmodels.h"
#include "assemblejsonfromplayeridandname.h"
#include "assemblejsonbasictournamentvalues.h"
#include "gettournamentindexesfromjson.h"
#include "getdeleteplayerindexfromjson.h"
#include "assembledartspointmodelfromjson.h"
#include "assembleplayermodelfromjson.h"
#include "assignplayeridstodartstournamentmodel.h"
#include "addplayernametodartsinputmodel.h"
#include "addplayernametodartsinputmodel.h"
#include "dartstournamentbuilder.h"
#include "AssembleDartsTournamentsFromJsonArray.h"
#include "assembledartspointsfromjson.h"
#include "dartspointjsondbservice.h"
#include "dartsscorejsondb.h"
#include "assemblejsonarrayfromdartspoints.h"
#include "assemblemultiattemptscoresbyjson.h"
#include "assemblejsonbydartsscoremodels.h"
#include "getinputmodelsservice.h"
#include "defaultdbmanipulatorservice.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "inputmodelscountservice.h"
#include "dartspointsjsonservice.h"
#include "dartsjsonservicebuilder.h"
#include "playerjsonservicebuilder.h"
#include "dartsmodelsservicebuilder.h"
#include "playermodelsservicebuilder.h"
#include "builddartspointservicewithlocaljsondb.h"
#include "builddartsscoreservicewithlocaljsondb.h"

namespace DartsModelsContext {
    class DefaultModelsServiceBuilder :
            public AbstractModelsServiceBuilder<AbstractModelsService>
    {
    public:
        static DefaultModelsServiceBuilder* createInstance();
        typedef IDartsScoreModelsService<IDartsScoreDb> ScoreModelsService;
        typedef IPlayerModelsJsonService<IPlayerModel,QUuid,QString,QByteArray> PlayerModelsJsonService;
        AbstractModelsService *buildLocalModelsServiceWithJsonDb() override;
    private:
        IDartsJsonServiceBuilder* _dartsJsonServiceBuilder = new DartsJsonServiceBuilder;
        IModelsServiceBuilder<PlayerModelsJsonService>* _playerJsonServiceBuilder  = new PlayerJsonServiceBuilder;
        IModelsServiceBuilder<IDartsModelsService>* _localDartsTournamentServiceBuilder = new DartsModelsServiceBuilder;
        IModelsServiceBuilder<ScoreModelsService>* _dartsScoreModelsServiceBuilder = new BuildDartsScoreServiceWithLocalJsonDb;
        IModelsServiceBuilder<IDartsPointModelsService<IDartsPointDb>>* _dartsPointModelsServiceBuilder = new BuildDartsPointServiceWithLocalJsonDb;
        IModelsServiceBuilder<IPlayerModelsService>* _playerServiceBuilder = new PlayerModelsServiceBuilder;
    };
}


#endif // DEFAULTMODELSSERVICEBUILDER_H
