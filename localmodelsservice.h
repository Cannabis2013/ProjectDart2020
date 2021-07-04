#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include "abstractmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartstournamentsdbmanipulator.h"
#include "iplayermodel.h"
#include <QVariantList>
#include "idartsjsonmanipulator.h"
#include "igetdatafromjson.h"
#include "dartsscoreinput.h"
#include "dartspointinput.h"
#include "idartstournament.h"
#include "idartstournamentbuilder.h"
#include "idartsscoremodelsservice.h"
#include "idartspointmodelsservice.h"
#include "idartsinputdb.h"
#include "iplayerinputsdbmanipulatorservice.h"
#include "igetinputmodelsservice.h"
#include "ipredicate.h"
#include "iinputmodelscountservice.h"
#include "idartspointsjsonservice.h"
#include "idartsscorejsonservice.h"
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

namespace DartsModelsContext {
    class LocalModelsService : public AbstractModelsService
    {
    public:
        /*
         * Public types
         */
        enum TournamentModelsContextResponse{
            TournamentCreatedOK = 0x32,
            TournamentDeletedOK = 0x35,
            EndOfTransmission = 0x10,
            ModelsStatePersisted = 0x47
        };
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        // Typedefs ;
        typedef IDartsTournamentBuilder<IDartsTournament,QByteArray> TournamentBuilder;
        typedef IModelsDbContext<IPlayerInput> DbService;
        typedef IPlayerInputsDbManipulatorService<IPlayerInput,DbService,QUuid> DbServiceManipulator;
        typedef IGetInputModelsService<IPlayerInput,DbService,QUuid> IGetInputModels;
        typedef IPredicate<IPlayerInput> Predicate;
        typedef QVector<const IPlayerInput*> PlayerInputs; ;
        typedef IBinaryService<const PlayerInputs&,
                               const Predicate*,
                               PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsScoreModelsService<IDartsInputDb> ScoreModelsService;
        typedef IInputModelsCountService<DbService,QUuid> CountInputModels;
        typedef IDartsPointsJsonService<IPlayerInput,IDartsPointIndexes,QByteArray> PointModelsJsonService;
        typedef IDartsScoreJsonService<IPlayerInput,IDartsScoreIndexes,QByteArray> ScoreModelsJsonService;
        /*
         * Create instance
         */
        static LocalModelsService* createInstance();
    public slots:
        /*
         * General tournaments methods
         */
        void deleteTournaments(const QByteArray &json) override;
        void handleRequestGameMode(const int &index) override;
        void handleRequestTournaments() override;
        void resetDartsPointTournament(const QUuid &tournamentId) override;
        void resetDartsScoreTournament(const QUuid &tournamentId) override;
        void setDartsTournamentWinner(const QByteArray &json) override;
        /*
         * Darts tournaments methods
         */
        void addDartsTournament(const QByteArray &json) override;
        void assembleDartsTournamentDataFromId(const QUuid& tournamentId) override;
        /*
         * Darts single attempt point methods
         */
        void getOrderedDartsPoints(const QUuid &tournamentId) override;
        void addDartsPoint(const QByteArray& json) override;
        void assembleAssignedPlayerPoints(const QUuid &tournamentId) override;
        virtual void assembleDartsPointIndexes(const QUuid &tournamentId) override;
        void hideDartsPoint(const QUuid& tournamentId,
                                const QUuid& playerId,
                                const int& roundIndex,
                                const int& attemptIndex) override;
        void revealPoint(const QUuid& tournamentId,
                             const QUuid& playerId,
                             const int& roundIndex,
                             const int& attemptIndex) override;
        /*
         * Darts multiattempt score methods
         */
        void assembleAssignedPlayerScores(const QUuid &tournamentId) override;
        void assembleDartsScoreIndexes(const QUuid &tournamentId) override;
        void addDartsScore(const QByteArray &json) override;
        void hideDartsScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        void revealScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        /*
         * Send tournament values
         */
        void assembleDartsKeyValues(const QUuid& tournament) override;

        /*
         * Player models context related methods
         */
        void createPlayer(const QByteArray &json) override;
        void deletePlayerFromIndex(const QByteArray& json) override;

        void deletePlayersFromIndexes(const QByteArray& json) override;
        void handleRequestPlayersDetails() override;
        void assembleAssignedPlayerEntities(const QUuid &tournamentId) override;
        void assembleDartsTournamentWinnerIdAndName(const QUuid &tournamentId) override;
    protected:
        // Builder services
        TournamentBuilder* _dartsTournamentBuilder;
        // services
        IDartsJsonManipulator* _dartsJsonManipulator;
        // Tournament services
        IDartsModelManipulator *_dartsModelManipulator;
        IDartsTournamentJsonBuilder *_createJsonFromDartsTournamentModels;
        IGetDartsTournamentFromDb *_getDartsTournamentByDb;
        IGetDataFromDartsTournament<ITournament> *_getDataFromDartsTournament;
        // Input services
        PointModelsJsonService* _dartsPointsJsonService;
        ScoreModelsJsonService* _dartsScoresJsonService;
        IDartsPointModelsService<IDartsInputDb>* _dartsPointInputService;
        SortDartsInputsByPredicateService* _inputModelsSortService;
        ScoreModelsService* _dartsScoreInputService;
        IGetInputModels* _getInputModelsService;
        CountInputModels* _inputModelsScountervice;
        Predicate* _sortPointInputsByIndexes;
        IBinaryService<const IModel<QUuid,QByteArray>*,
                       const QString&,
                       const IModel<QUuid,QByteArray>*>* _addPlayerNameToDartsInputModel;
        // Player related services
        IDartsPlayerModelBuilder *_playerModelBuilder;
        IGetDataFromPlayerModels *_getDataFromPlayerModels;
        IGetDartsPlayerDataFromDb * _getDartsPlayerDataFromDb;
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
        IDartsInputDb* _dartsPointInputDb;
        IDartsInputDb* _dartsScoreInputDb;
        IDartsTournamentDb *_dartsTournamentDb;
        IPlayerModelsDb *_dartsPlayerDb;
    };
}


#endif // MODELCONTEXTINTERFACE_H
