#ifndef JSONDARTSMODELSSERVICE_H
#define JSONDARTSMODELSSERVICE_H

#include "localdartsmodelsservice.h"
// Genereic models includes
#include "defaultdbmanipulatorservice.h"
// Input models includes
#include "dartspointjsondb.h"
#include "dartsinputjsondb.h"
#include "addplayernametodartsinputmodel.h"
#include "dartsscoremodelmanipulator.h"
#include "dartspointmodelsservice.h"
#include "getinputmodelsservice.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "inputmodelscountservice.h"
#include "dartspointsjsonservice.h"
#include "dartscreatejsonfromscores.h"
#include "dartspointjsondb.h"
#include "dartsscorejsondb.h"
#include "dartsinputsfilterservice.h"
#include "createdartsscoreindexes.h"
#include "getdartsscorefromdb.h"
#include "getdartspointfromdb.h"
// Player models includes
#include "getdartsplayerdatafromdb.h"
#include "dartsplayerjsonbuilder.h"
#include "dartsplayermodelbuilder.h"
#include "playermodelsjsondb.h"
#include "playermodelslocaljsondb.h"
#include "getdatafromplayermodels.h"
// Tournament models includes
#include "dartstournamentdbmanipulator.h"
#include "adddetailstotournamentjson.h"
#include "tournamentsjsondb.h"
#include "dartstournamentbuilder.h"
#include "dartstournamentjsonbuilder.h"
#include "dartstournamentsjsondb.h"
#include "getdartstournamentfromdb.h"
#include "getdartstournamentdatafromjson.h"
#include "dartsmodelmanipulator.h"
#include "getdatafromdartstournament.h"
#include "dartscreatejsonfromscoreindexes.h"

class JsonDartsModelsService : public DartsModelsContext::LocalDartsModelsService
{
public:
    JsonDartsModelsService()
    {
        using namespace DartsModelsContext;
        _tournamentDbManipulator = new DartsTournamentDbManipulator;
        _addToDartsTournament = new AddDetailsToTournamentJson;
        _dartsScoreInputService = new DartsScoreModelManipulator;
        _dartsPointInputService = new DartsPointModelsService;
        _addPlayerNameToDartsInputModel = new AddPlayerNameToDartsInputModel;
        _dartsTournamentBuilder = new DartsTournamentBuilder;
        _dartsPointsDb = new DartsDbContext::DartsPointJsonDb;
        _dartsScoresDb = new DartsDbContext::DartsScoreJsonDb;
        _dartsTournamentDb = new DartsTournamentsJsonDb;
        _getInputsFromDb = new GetInputModelsService;
        _dbManipulatorService = new DefaultDbManipulatorService;
        _sortInputs = new InputModelsSortService;
        _sortPointInputsByIndexes = new SortDartsPointInputsByIndexes;
        _countInputs = new InputModelsCountService;
        _dartsPointsJsonService = new DartsModelsCreateJsonFromPoints;
        _createJsonFromScoreModels = new DartsCreateJsonFromScores;
        _getDartsPlayerData = new GetDartsPlayerDataFromDb;
        _dartsPlayerJsonBuilder = new DartsPlayerJsonBuilder;
        _getTournament = new GetDartsTournamentFromDb;
        _createJsonFromDartsTournamentModels = new DartsTournamentJsonBuilder;
        _playerModelBuilder = new DartsPlayerModelBuilder;
        _dartsPlayersDb = new PlayerModelsLocalJsonDb;
        _getDartsTournamentDataFromJson = new GetDartsTournamentDataFromjson;
        _dartsModelManipulator = new DartsModelManipulator;
        _getDataFromPlayerModels = new GetDataFromPlayerModels;
        _getDataFromDartsTournament = new GetDataFromDartsTournament;
        _createIndexesFromScoreModels = new CreateDartsScoreIndexes;
        _createJsonfromScoreIndexes = new DartsCreateJsonFromScoreIndexes;
        _getScoreFromDb = new GetDartsScoreFromDb;
        _getPointFromDb = new GetDartsPointFromDb;
    }
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
