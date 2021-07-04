#ifndef LOCALMODELSSERVICEWITHJSONDB_H
#define LOCALMODELSSERVICEWITHJSONDB_H

#include "localmodelsservice.h"
#include "dartspointjsondb.h"
#include "dartsinputjsondb.h"
#include "tournamentsjsondb.h"
#include "createdartstournamentsfromjson.h"
#include "createjsonfromdartstournaments.h"
#include "dartstournamentdbmanipulator.h"
#include "dartsjsonmanipulator.h"
#include "dartsscoremodelsservice.h"
#include "dartspointmodelsservice.h"
#include "addplayernametodartsinputmodel.h"
#include "dartstournamentbuilder.h"
#include "getinputmodelsservice.h"
#include "defaultdbmanipulatorservice.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "inputmodelscountservice.h"
#include "dartspointsjsonservice.h"
#include "dartsscorejsonservice.h"
#include "getdartsplayerdatafromdb.h"
#include "getdartstournamentfromdb.h"
#include "dartstournamentjsonbuilder.h"
#include "playermodelsjsondb.h"
#include "dartsplayerjsonbuilder.h"
#include "dartsplayermodelbuilder.h"
#include "dartspointjsondb.h"
#include "dartsscorejsondb.h"
#include "dartstournamentsjsondb.h"
#include "playermodelslocaljsondb.h"
#include "getdartstournamentdatafromjson.h"
#include "dartsmodelmanipulator.h"
#include "getdatafromplayermodels.h"

class LocalModelsServiceWithJsonDb : public DartsModelsContext::LocalModelsService
{
public:
    LocalModelsServiceWithJsonDb()
    {
        using namespace DartsModelsContext;
        _tournamentDbManipulator = new DartsTournamentDbManipulator;
        _dartsJsonManipulator = new DartsJsonManipulator;
        _dartsScoreInputService = new DartsScoreModelsService;
        _dartsPointInputService = new DartsPointModelsService;
        _addPlayerNameToDartsInputModel = new AddPlayerNameToDartsInputModel;
        _dartsTournamentBuilder = new DartsTournamentBuilder;
        _dartsPointInputDb = new DartsPointJsonDb;
        _dartsScoreInputDb = new DartsScoreJsonDb;
        _dartsTournamentDb = new DartsTournamentsJsonDb;
        _getInputModelsService = new GetInputModelsService;
        _dbManipulatorService = new DefaultDbManipulatorService;
        _inputModelsSortService = new InputModelsSortService;
        _sortPointInputsByIndexes = new SortDartsPointInputsByIndexes;
        _inputModelsScountervice = new InputModelsCountService;
        _dartsPointsJsonService = new DartsPointsJsonService;
        _dartsScoresJsonService = new DartsScoreJsonService;
        _getDartsPlayerDataFromDb = new GetDartsPlayerDataFromDb;
        _dartsPlayerJsonBuilder = new DartsPlayerJsonBuilder;
        _getDartsTournamentByDb = new GetDartsTournamentFromDb;
        _createJsonFromDartsTournamentModels = new DartsTournamentJsonBuilder;
        _playerModelBuilder = new DartsPlayerModelBuilder;
        _dartsPlayerDb = new PlayerModelsLocalJsonDb;
        _getDartsTournamentDataFromJson = new GetDartsTournamentDataFromjson;
        _dartsModelManipulator = new DartsModelManipulator;
        _getDataFromPlayerModels = new GetDataFromPlayerModels;
    }
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
