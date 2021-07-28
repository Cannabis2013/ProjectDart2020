#ifndef LOCALMODELSSERVICE_H
#define LOCALMODELSSERVICE_H
#include "abstractdartsmodelscontext.h"
#include "dartsinputservices.h"
#include "dartstournamentservices.h"
#include "playermodelsservices.h"
#include "dartsutilityservices.h"

namespace ModelsContext {
    class DartsModelsService :
            public AbstractDartsModelsContext,
            public DartsTournamentServices,
            public DartsInputServices,
            public DartsUtilityServices
    {
    public:
        //Public types
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
    public slots:
        //General tournaments methods
        void deleteTournaments(const QVector<int> &indexes) override;
        void handleRequestGameMode(const int &index) override;
        void handleRequestTournaments() override;
        void resetDartsPointTournament(const QUuid &tournamentId) override;
        void resetDartsScoreTournament(const QUuid &tournamentId) override;
        void setDartsTournamentWinner(const QByteArray &json) override;
        //Darts tournaments methods
        void addDartsTournament(const QByteArray &json, const QVector<const IModel<QUuid> *> &playerModels) override;
        void createDartsMetaData(const QUuid& tournamentId) override;
        void createAssignedPlayerEntities(const QUuid &tournamentId) override;
        void createDartsTournamentWinnerIdAndName(const QUuid &tournamentId) override;
        //Darts point methods
        void getOrderedDartsPoints(const QUuid &tournamentId) override;
        void addDartsPoint(const QByteArray& json) override;
        void createAssignedPlayerPoints(const QUuid &tournamentId) override;
        virtual void createDartsPointIndexes(const QUuid &tournamentId) override;
        void hideDartsPoint(const QUuid& tournamentId,const QUuid& playerId,
                            const int& roundIndex,const int& attemptIndex) override;
        void revealPoint(const QUuid& tournamentId,const QUuid& playerId,
                         const int& roundIndex,const int& attemptIndex) override;
        //Darts multiattempt score methods
        void createAssignedPlayerScores(const QUuid &tournamentId) override;
        void createDartsScoreIndexes(const QUuid &tournamentId) override;
        void addDartsScore(const QByteArray &json) override;
        void hideDartsScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        void revealScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
        // Send tournament values
        void createDartsKeyValues(const QUuid& tournament) override;
    };
}
#endif // LOCALMODELSSERVICE_H
