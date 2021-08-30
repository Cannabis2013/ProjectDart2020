#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include <dscscoreservicesprovider.h>
#include <quuid.h>
#include "abstractdartsscorecontroller.h"
#include "dscservicesprovider.h"
#include "dsjsonservices.h"
class DSController : public AbstractDartsScoreController,
                     protected DSCServicesProvider,
                     protected DSJsonServices,
                     protected DSCScoreServicesProvider
{
    Q_OBJECT
public:
    // Public types
    enum InputDomains {
        PointDomain = 0x01,
        CriticalDomain = 0x02,
        OutsideDomain = 0x03,
        TargetDomain = 0x4,
        InputOutOfRange = 0x5
    };
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    enum ControllerState {
        WinnerDeclared = 0x15
    };
    static DSController* createInstance();
public slots:
    void beginInitialize() override;
    virtual void initializeControllerIndexes(const QByteArray& json) override;
    void initializeControllerPlayerDetails(const QByteArray &json) override;
    void initializeControllerDartsScores(const QByteArray &json) override;
    void initializeControllerWinnerIdAndName(const QByteArray &json) override;
    void start() override;
    void stop() override;
    void undoTurn() override;
    void redoTurn() override;
    void handleRequestForCurrentTournamentMetaData() override;
    void createOrderedDartsScores() override;
    void handleRequestDartsScores() override;
    void handleRequestFromUI() override;
    void handleAndProcessUserInput(const QByteArray &json) override;
    void handleScoreAddedToDataContext(const QByteArray& json) override;
    void handleResetTournament() override;
    void undoSuccess(const QByteArray &json) override;
    void redoSuccess(const QByteArray &json) override;
private:
    void createAndSendTurnValues(const QByteArray &json);
    void createAndSendWinnerValues();
    void subtractAndAddScoreToModel(DSCContext::IDSCModel * const scoreModel);
    QByteArray createJsonResponse(const QUuid &winnerId, const QString &winnerName);
    QByteArray createJsonResponse(DSCContext::IDSCModel *scoreModel,
                                  const DSCContext::DartsScoreTurnValues* turnValues);
    QByteArray createJsonResponse(DSCContext::IDSCModel *scoreModel, const DSCContext::IDSCIndexes* indexes,
                                  const DCContext::IDCPlayer *playerModel);
    void processDomain(const int& domain, const int &score);
    void sendCurrentTurnValues();
    QString currentPlayerName()  ;
    QUuid currentPlayerId();
    int lastPlayerIndex();
    void addScore(const int &score);
    void nextTurn();
    void declareWinner();
};

#endif // FIVEHUNDREDANDONEGAME_H
