#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <dcbuilderservices.h>
#include <dcindexservices.h>
#include <dcscoreservices.h>
#include <quuid.h>
#include "DCPlayerServices.h"
#include "abstractdartscontroller.h"
#include "dcbasicservices.h"
#include "dcjsonservices.h"
#include "jsonmerger.h"
#include "DartsMetaCollection/dcmetaservices.h"
class DartsController : public AbstractDartsController,
                        protected DCBasicServices,
                        protected DCMetaServices,
                        protected DCBuilderServices,
                        protected DCJsonServices,
                        protected DCScoreServices,
                        protected DCPlayerServices,
                        protected DCIndexServices
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
public slots:
    void beginInitialize() override;
    void initializeControllerIndexes(const QByteArray& json) override;
    void initializePlayerDetails(const QByteArray &json) override;
    void initializeScores(const QByteArray &json) override;
    void initializeWinnerDetails(const QByteArray &json) override;
    void handleOrderedInputs(const QByteArray &json) override;
    void start() override;
    void stop() override;
    void undoTurn() override;
    void redoTurn() override;
    void handleRequestForCurrentTournamentMetaData() override;
    void createDartsScores() override;
    void getOrderedInputsWithTotalScores() override;
    void handleRequestFromUI() override;
    void handleUserInput(const QByteArray &json) override;
    void handleUserInputAdded(const QByteArray& json) override;
    void handleResetTournament() override;
    void undoSuccess(const QByteArray &json) override;
    void redoSuccess(const QByteArray &json) override;
private:
    void updateTotalScore(const QByteArray &json);
    void createAndSendWinnerValues();
    void processDomain(const int& domain, DCContext::IDCModel *inputModel);
    void sendCurrentTurnValues();
    int lastPlayerIndex();
    void addInput(DCContext::IDCModel *inputModel);
    void nextTurn();
    void declareWinner();
};

#endif // FIVEHUNDREDANDONEGAME_H
