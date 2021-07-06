#ifndef LOCALDARTSMODELSSERVICE_H
#define LOCALDARTSMODELSSERVICE_H

#include "abstractmodelsservice.h"
#include "DefaultDartsServiceProvider.h"

namespace DartsModelsContext {
    class LocalDartsModelsService :
            public AbstractModelsService,
            protected DefaultDartsServiceProvider
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
        /*
         * Create instance
         */
        static LocalDartsModelsService *createInstance();
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
        void createDartsTournamentDataFromId(const QUuid& tournamentId) override;
        /*
         * Darts point methods
         */
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
        /*
         * Darts multiattempt score methods
         */
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
    };
}


#endif // MODELCONTEXTINTERFACE_H
