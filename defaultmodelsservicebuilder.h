#ifndef DEFAULTMODELSSERVICEBUILDER_H
#define DEFAULTMODELSSERVICEBUILDER_H

#include "abstractmodelsservicebuilder.h"
#include "abstractmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "localmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iplayermodel.h"
#include "getplayerindexesfromjson.h"
#include "assemblejsonfromdartspointindexes.h"
#include "jsonarrayfromplayernamesandids.h"
#include "assemblejsonfromdartspoints.h"
#include "assemblejsonfromordereddartspointmodels.h"
#include "assembledartstournamentmodelfromjson.h"
#include "assemblejsonbasictournamentvaluesfrommodel.h"
#include "assemblejsondartstournamentmodels.h"
#include "ibinaryservice.h"
#include "assemblejsonfromplayeridandname.h"
#include "assemblejsonbasictournamentvalues.h"
#include "gettournamentindexesfromjson.h"
#include "getdeleteplayerindexfromjson.h"
#include "assembledartspointmodelfromjson.h"
#include "assembleplayermodelfromjson.h"
#include "assignplayeridstodartstournamentmodel.h"
#include "addplayernametodartsinputmodel.h"
#include "idartsjsonservice.h"
#include "addplayernametodartsinputmodel.h"
#include "dartstournamentbuilder.h"
#include "idartsscoremodelsservice.h"
#include "idartspointmodelsservice.h"
#include "AssembleDartsTournamentsFromJsonArray.h"
#include "assemblesingleattemptpointsfromjson.h"
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
class DefaultModelsServiceBuilder :
        public AbstractModelsServiceBuilder<AbstractModelsService>
{
public:
    static DefaultModelsServiceBuilder* createInstance();
    typedef IDartsScoreModelsService<IDartsScoreDb> ScoreModelsService;
    AbstractModelsService *buildLocalModelsServiceWithJsonDb() override;
    DefaultModelsServiceBuilder* setModelsTournamentServiceBuilder(IModelsServiceBuilder<IDartsModelsService>* builder);
    DefaultModelsServiceBuilder* setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService> *playerServiceBuilder);
    DefaultModelsServiceBuilder* setDartsJSonServiceBuilder(IModelsServiceBuilder<IDartsJsonService> *dartsJSonServiceBuilder);
    DefaultModelsServiceBuilder* setDartsScoreModelsServiceBuilder(IModelsServiceBuilder<ScoreModelsService> *newDartsScoreModelsServiceBuilder);
    DefaultModelsServiceBuilder* setDartsPointModelsServiceBuilder(IModelsServiceBuilder<IDartsPointModelsService<IDartsPointDb>> *newDartsPointModelsServiceBuilder);

private:
    IModelsServiceBuilder<IDartsJsonService>* _dartsJSonServiceBuilder;
    IModelsServiceBuilder<IDartsModelsService>* _localDartsTournamentServiceBuilder;
    IModelsServiceBuilder<ScoreModelsService>* _dartsScoreModelsServiceBuilder;
    IModelsServiceBuilder<IDartsPointModelsService<IDartsPointDb>>* _dartsPointModelsServiceBuilder;
    IModelsServiceBuilder<IPlayerModelsService>* _playerServiceBuilder;
};

#endif // DEFAULTMODELSSERVICEBUILDER_H
