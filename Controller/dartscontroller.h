#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <dcturnvaluesservices.h>
#include "DCIndexSLAs/dcindexservices.h"
#include "DCScoresSLAs/dcscoreservices.h"
#include <quuid.h>
#include "DCPlayerSLAs/DCPlayerServices.h"
#include "abstractdartscontroller.h"
#include "DCJsonSLAs/dcjsonservices.h"
#include "jsonmerger.h"
#include "DCMetaSLAs/dcmetaservices.h"
#include "DCInputSLAs/dcinputsservices.h"

class DartsController : public AbstractDartsController,
                        protected DCMetaServices,
                        protected DCTurnvaluesServices,
                        protected DCJsonServices,
                        protected DCScoreServices,
                        protected DCPlayerServices,
                        protected DCInputsServices,
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
    void processDomain(const int& domain, DCContext::IDCInputModel *inputModel);
    void sendCurrentTurnValues();
    int lastPlayerIndex();
    void addInput(DCContext::IDCInputModel *inputModel);
    void nextTurn();
    void declareWinner();
};

#endif // FIVEHUNDREDANDONEGAME_H
