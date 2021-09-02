#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <dcbuilderservices.h>
#include <dscscoreservices.h>
#include <quuid.h>
#include "abstractdartscontroller.h"
#include "dcbasicservices.h"
#include "dcjsonservices.h"
#include "jsonmerger.h"
class DartsController : public AbstractDartsController,
                        protected DCBasicServices,
                        protected DCBuilderServices,
                        protected DCJsonServices,
                        protected DSCScoreServices
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
    static DartsController* createInstance();
public slots:
    void beginInitialize() override;
    virtual void initializeControllerIndexes(const QByteArray& json) override;
    void initializePlayerDetails(const QByteArray &json) override;
    void initializeDartsScores(const QByteArray &json) override;
    void initializeWinnerDetails(const QByteArray &json) override;
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
    void updateTotalScore(const QByteArray &json);
    void createAndSendWinnerValues();
    QByteArray createJsonResponse(const QUuid &winnerId, const QString &winnerName);
    QByteArray createJsonResponse(DCContext::IDCModel *inputModel,
                                  const DCContext::DCTurnValues* turnValues);
    QByteArray createJsonResponse(DCContext::IDCModel *inputModel, const DCContext::IDCIndexes *indexes,
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
