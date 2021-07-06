#ifndef DEFAULTDARTSSERVICEPROVIDER_H
#define DEFAULTDARTSSERVICEPROVIDER_H

#include "iplayermodelsservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartstournamentsdbmanipulator.h"
#include "iplayermodel.h"
#include <QVariantList>
#include "iadddetailstotournamentjson.h"
#include "igetdatafromjson.h"
#include "dartsscoreinput.h"
#include "dartspointinput.h"
#include "idartstournament.h"
#include "idartstournamentbuilder.h"
#include "idartsscoremodelmanipulator.h"
#include "idartspointmodelmanipulator.h"
#include "idartsinputdb.h"
#include "iplayerinputsdbmanipulatorservice.h"
#include "igetinputmodelsservice.h"
#include "ipredicate.h"
#include "icountinputmodels.h"
#include "idartsmodelscreatejsonfrompoints.h"
#include "idartscreatejsonfromscores.h"
#include "idartstournamentdb.h"
#include "igetdartsplayerdatafromdb.h"
#include "igetdatafromplayermodels.h"
#include "iplayermodelsdb.h"
#include "idartsmodelmanipulator.h"
#include "idartstournamentjsonbuilder.h"
#include "igetdartstournamentfromdb.h"
#include "igetdartstournamentfromdb.h"
#include "idartsplayerjsonbuilder.h"
#include "igetdartstournamentdatafromjson.h"
#include "idartsplayermodelbuilder.h"
#include "idartsplayerdbmanipulator.h"
#include "igetdatafromdartstournament.h"
#include "igetdartsscorefromdb.h"
#include "igetdartspointfromdb.h"
#include "icreatedartsindexes.h"
#include "icreatejsonfromdartspointindexes.h"
#include "idartscreatejsonfromscoreindexes.h"
#include "idartscreatejsonfromscores.h"
#include "idartstournamentnumberofattempts.h"
#include "isortinputmodels.h"

namespace DartsModelsContext {
    class DefaultDartsServiceProvider
    {
    public:
        // Typedefs ;
        typedef IDartsTournamentBuilder<IDartsTournament,QByteArray> TournamentBuilder;
        typedef IModelsDbContext<IPlayerInput> DbService;
        typedef IPlayerInputsDbManipulatorService<IPlayerInput,DbService,QUuid> DbServiceManipulator;
        typedef IPredicate<IPlayerInput> Predicate;
        typedef QVector<const IPlayerInput*> PlayerInputs;
        typedef IDartsScoreModelManipulator<IDartsInputDb> ScoreModelsService;
    protected:
        // Builder services
        TournamentBuilder* _dartsTournamentBuilder;
        // services
        IAddDetailsToTournamentJson* _addToDartsTournament;
        // Tournament services
        IDartsModelManipulator *_dartsModelManipulator;
        IDartsTournamentJsonBuilder *_createJsonFromDartsTournamentModels;
        IGetDartsTournamentFromDb *_getTournament;
        IGetDataFromDartsTournament<ITournament> *_getDataFromDartsTournament;
        IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
        // Input services
        IDartsModelsCreateJsonFromPoints* _dartsPointsJsonService;
        IDartsCreateJsonFromScores* _createJsonFromScoreModels;
        IDartsPointModelManipulator *_dartsPointInputService;
        ISortInputModels* _sortInputs;
        ScoreModelsService* _dartsScoreInputService;
        IGetInputModelsService* _getInputsFromDb;
        ICountInputModels* _countInputs;
        Predicate* _sortPointInputsByIndexes;
        Predicate *_sortScoreInputsByIndexes;
        IBinaryService<const IModel<QUuid,QByteArray>*,
                       const QString&,
                       const IModel<QUuid,QByteArray>*>* _addPlayerNameToDartsInputModel;
        ICreateDartsIndexes<IDartsScoreIndexes> *_createIndexesFromScoreModels;
        ICreateDartsIndexes<IDartsPointIndexes> *_createIndexesFromPointModels;
        IGetDartsScoreFromDb *_getScoreFromDb;
        IGetDartsPointFromDb *_getPointFromDb;
        ICreateJsonfromDartsPointIndexes *_createJsonFromPointIndexes;
        IDartsCreateJsonFromScoreIndexes *_createJsonfromScoreIndexes;
        // Player related services
        IDartsPlayerModelBuilder *_playerModelBuilder;
        IGetDataFromPlayerModels *_getDataFromPlayerModels;
        IGetDartsPlayerDataFromDb * _getDartsPlayerData;
        IDartsPlayerJsonBuilder *_dartsPlayerJsonBuilder;
        IDartsPlayerDbManipulator *_playerDbManipulator;
        // Json
        IGetDartsTournamentDataFromJson *_getDartsTournamentDataFromJson;
        // Db manipulator services
        IDartsTournamentsDbManipulator* _tournamentDbManipulator;
        DbServiceManipulator* _dbManipulatorService;
        // Db services
        IGetDataFromPlayerModels *_playerListService;
        // Db contexts
        IDartsInputDb* _dartsPointsDb;
        IDartsInputDb* _dartsScoresDb;
        IDartsTournamentDb *_dartsTournamentDb;
        IPlayerModelsDb *_dartsPlayersDb;
    };
}

#endif // DEFAULTSERVICEPROVIDER_H
