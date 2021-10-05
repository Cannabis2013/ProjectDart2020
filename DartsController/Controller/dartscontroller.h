#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "DartsController/DCTurnValuesSLAs/dcturnvaluesservices.h"
#include "DartsController/DCIndexSLAs/dcindexservices.h"
#include "DartsController/DCScoresSLAs/dcscoreservices.h"
#include <quuid.h>
#include "DartsController/DCPlayerSLAs/DCPlayerServices.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartsController/DCJsonSLAs/dcjsonservices.h"
#include "DartsController/DCMetaSLAs/dcmetaservices.h"
#include "DartsController/DCInputSLAs/dcinputsservices.h"

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
private slots:
    void persistInput(DCContext::IDCInputModel *inputModel);
    void nullifyAndPersistInput(DCContext::IDCInputModel *input);
    void declareWinner(DCContext::IDCInputModel *input);
private:
    QByteArray assembleJsonResponse(DCContext::IDCInputModel *input, const DCContext::DCTurnValues *turnValues);
    QByteArray assembleJsonResponse(DCContext::IDCInputModel *input, const DCContext::IDCIndexes *indexes);
    void connectInputEvaluator();
    void updateTotalScore(DCContext::IDCInputModel *input);
    void createAndSendWinnerValues();
    void sendCurrentTurnValues();
    int lastPlayerIndex();
};
#endif // FIVEHUNDREDANDONEGAME_H
