#ifndef LOCALMODELSSERVICE_H
#define LOCALMODELSSERVICE_H
#include "abstractdartsmodelscontext.h"
#include "dartsinputservices.h"
#include "dartstournamentservices.h"
#include "playermodelsservices.h"
#include "dartsutilityservices.h"

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
    void getGameMode(const int &index) override;
    void getTournaments() override;
    void resetDartsPointTournament(const QUuid &tournamentId) override;
    void setDartsTournamentWinner(const QByteArray &json) override;
    //Darts tournaments methods
    void addDartsTournament(const QByteArray &json, const QVector<const IModel<QUuid> *> &playerModels) override;
    void createDartsMetaData(const QUuid& tournamentId) override;
    void getPlayerDetails(const QUuid &tournamentId) override;
    void getTournamentWinnerDetails(const QUuid &tournamentId) override;
    //Darts point methods
    void getOrderedInputs(const QUuid &tournamentId) override;
    void addInput(const QByteArray& json) override;
    void getPlayerInputs(const QUuid &tournamentId) override;
    virtual void createIndexes(const QUuid &tournamentId) override;
    void hideInput(const QUuid& tournamentId,const QUuid& playerId,
                   const int& roundIndex, const int& attemptIndex) override;
    void revealInput(const QUuid& tournamentId,const QUuid& playerId,
                     const int& roundIndex,const int& attemptIndex) override;
    //Darts multiattempt score methods
    // Send tournament values
    void createDartsKeyValues(const QUuid& tournament) override;
};
#endif // LOCALMODELSSERVICE_H
