#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include "abstractmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartsmodelsservice.h"
#include "iplayermodel.h"
#include <QVariantList>
#include "idartsjsonservice.h"
#include "dartsscoreinput.h"
#include "dartspointinput.h"
#include "idartstournament.h"
#include "idartstournamentbuilder.h"
#include "idartsscoremodelsservice.h"
#include "idartspointmodelsservice.h"
#include "idartspointdb.h"
#include "idartsscoredb.h"
#include "iplayerinputsdbmanipulatorservice.h"
#include "igetinputmodelsservice.h"
#include "ipredicate.h"
#include "iinputmodelscountservice.h"
#include "idartspointsjsonservice.h"
#include "idartsscorejsonservice.h"
#include "iplayermodelsjsonservice.h"
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
        typedef IDartsTournamentBuilder<IDartsTournament,QByteArray> DartsTournamentBuilder;
        typedef IModelsDbContext<IPlayerInput> DbService;
        typedef IPlayerInputsDbManipulatorService<IPlayerInput,DbService,QUuid> DbServiceManipulator;
        typedef IGetInputModelsService<IPlayerInput,DbService,QUuid> GetInputModelsService;
        typedef IPredicate<IPlayerInput> Predicate;
        typedef QVector<const IPlayerInput*> PlayerInputs; ;
        typedef IBinaryService<const PlayerInputs&,
                               const Predicate*,
                               PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsScoreModelsService<IDartsScoreDb> DartsScoreModelsService;
        typedef IInputModelsCountService<DbService,QUuid> InputModelsCountService;
        typedef IDartsPointsJsonService<IPlayerInput,IPlayerModelsService,IDartsPointIndexes,QByteArray> PointModelsJsonService;
        typedef IDartsScoreJsonService<IPlayerInput,IDartsScoreIndexes,QByteArray> ScoreModelsJsonService;
        typedef IPlayerModelsJsonService<IPlayerModel,QUuid,QString,QByteArray> PlayerModelsJsonService;
        /*
         * Create instance
         */
        static LocalModelsService* createInstance();

        // Set service methods
        LocalModelsService* setDartsModelsService(IDartsModelsService *dartsModelsService);
        LocalModelsService* setPlayerModelsService(IPlayerModelsService *playerModelsContext);
        LocalModelsService* setDartsJsonService(IDartsJsonService *dartsJsonService);
        LocalModelsService* setAddPlayerNameToDartsInputModel(IBinaryService<const IModel<QUuid,QByteArray> *,
                                                              const QString &,
                                                              const IModel<QUuid,QByteArray> *> *service);
        LocalModelsService* setDartsTournamentBuilder(DartsTournamentBuilder *newDartsTournamentBuilder);
        LocalModelsService* setDartsScoreInputModelsService(DartsScoreModelsService *service);
        LocalModelsService* setDartsPointInputService(IDartsPointModelsService<IDartsPointDb> *newDartsPointInputService);
        LocalModelsService* setDartsPointInputDb(IDartsPointDb *newDartsPointInputDb);
        LocalModelsService* setDartsScoreInputDb(IDartsScoreDb *newDartsScoreInputDb);
        LocalModelsService* setDbManipulatorService(DbServiceManipulator *newDbManipulatorService);
        LocalModelsService* setGetInputModelsService(GetInputModelsService *newGetInputModelsService);
        LocalModelsService* setInputModelsSortService(SortDartsInputsByPredicateService *newSortInputModelsService);
        LocalModelsService* setSortPointInputsByIndexes(Predicate *newSortPointInputsByIndexes);
        LocalModelsService* setInputModelsScountervice(InputModelsCountService *newInputModelsScountervice);
        LocalModelsService* setPointModelsJsonService(PointModelsJsonService *newPointModelsJsonService);
        LocalModelsService* setDartsScoresJsonService(ScoreModelsJsonService *newDartsScoresJsonService);
        LocalModelsService* setDartsPointsJsonService(PointModelsJsonService *newDartsPointsJsonService);
        LocalModelsService* setPlayerModelsJsonService(PlayerModelsJsonService *newPlayerModelsJsonService);

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
        void assembleDartsScoreIndexes(const QUuid &tournament) override;
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
    private:

        // Builder services
        DartsTournamentBuilder* _dartsTournamentBuilder;
        // services
        IDartsJsonService* _dartsJsonService;
        PointModelsJsonService* _dartsPointsJsonService;
        ScoreModelsJsonService* _dartsScoresJsonService;
        PlayerModelsJsonService* _playerModelsJsonService;
        SortDartsInputsByPredicateService* _inputModelsSortService;
        IDartsModelsService* _dartsModelsService;
        IPlayerModelsService* _playerModelsService;
        DartsScoreModelsService* _dartsScoreInputService;
        IDartsPointModelsService<IDartsPointDb>* _dartsPointInputService;
        IBinaryService<const IModel<QUuid,QByteArray>*,
                       const QString&,
                       const IModel<QUuid,QByteArray>*>* _addPlayerNameToDartsInputModel;
        GetInputModelsService* _getInputModelsService;
        Predicate* _sortPointInputsByIndexes;
        InputModelsCountService* _inputModelsScountervice;
        // Db manipulator services
        DbServiceManipulator* _dbManipulatorService;
        // Db services
        IDartsPointDb* _dartsPointInputDb;
        IDartsScoreDb* _dartsScoreInputDb;
    };
}


#endif // MODELCONTEXTINTERFACE_H
