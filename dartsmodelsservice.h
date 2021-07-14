#ifndef DARTSMODELSSERVICE_H
#define DARTSMODELSSERVICE_H
#include "abstractmodelsservice.h"
#include "dartsinputservices.h"
#include "dartstournamentservices.h"
#include "playermodelsservices.h"
#include "dartsutilityservices.h"

namespace DartsModelsContext {
    class DartsModelsService : public AbstractModelsService,
                               public DartsTournamentServices,
                               public DartsInputServices,
                               public PlayerModelsServices,
                               public DartsUtilityServices
    {
    public:
        //Public types
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
    public slots:
        //General tournaments methods
        void deleteTournaments(const QByteArray &json) override;
        void handleRequestGameMode(const int &index) override;
        void handleRequestTournaments() override;
        void resetDartsPointTournament(const QUuid &tournamentId) override;
        void resetDartsScoreTournament(const QUuid &tournamentId) override;
        void setDartsTournamentWinner(const QByteArray &json) override;
        //Darts tournaments methods
        void addDartsTournament(const QByteArray &json) override;
        void createDartsMetaData(const QUuid& tournamentId) override;
        //Darts point methods
        void getOrderedDartsPoints(const QUuid &tournamentId) override;
        void addDartsPoint(const QByteArray& json) override;
        void createAssignedPlayerPoints(const QUuid &tournamentId) override;
        virtual void createDartsPointIndexes(const QUuid &tournamentId) override;
        void hideDartsPoint(const QUuid& tournamentId,
                                const QUuid& playerId,
                                const int& roundIndex,
                                const int& attemptIndex) override;
        void revealPoint(const QUuid& tournamentId,
                             const QUuid& playerId,
                             const int& roundIndex,
                             const int& attemptIndex) override;
        //Darts multiattempt score methods
        void createAssignedPlayerScores(const QUuid &tournamentId) override;
        void createDartsScoreIndexes(const QUuid &tournamentId) override;
        void addDartsScore(const QByteArray &json) override;
        void hideDartsScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        void revealScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        /*
         * Send tournament values
         */
        void createDartsKeyValues(const QUuid& tournament) override;
        /*
         * Player models context related methods
         */
        void createPlayer(const QByteArray &json) override;
        void deletePlayerFromIndex(const QByteArray& json) override;
        void deletePlayersFromIndexes(const QByteArray& json) override;
        void handleRequestPlayersDetails() override;
        void createAssignedPlayerEntities(const QUuid &tournamentId) override;
        void createDartsTournamentWinnerIdAndName(const QUuid &tournamentId) override;
    private:
        const IPlayerModel *getTournamentWinnerModel(const QUuid &tournamentId);
        void removeInputs(const QUuid &tournamentId, IDartsInputDb *dbService);
        QVector<const IPlayerModel*> createPlayerModelsFromJson(const QByteArray &json);
        void addPlayerIdsAndNAmesToTournament(const ITournament *model, const QVector<const IPlayerModel *> &playerModels);
        QByteArray createTournamentWinnerJson(const QUuid &winnerId);
        void setTournamentWinnerId(const QUuid &tournamentId, const QUuid &winnerId,
                                   const IGetDartsTournamentFromDb *getTournament,
                                   IDartsModelManipulator *dbManipulator) const;
        const IPlayerInput *createAndAddInput(const QByteArray &json, const IDartsCreateInput *createService, IDartsInputDb *dbService);
        void removeHiddenInputs(const QUuid &tournamentId, IDartsInputDb *dbService);
    };
}
#endif // MODELCONTEXTINTERFACE_H
