#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DartsController/DCIndexSLAs/dcindexslas.h"
#include "DartsController/DCScoresSLAs/dcscoreslas.h"
#include <quuid.h>
#include "DartsController/DCPlayerSLAs/DCPlayerSLAs.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartsController/DCJsonSLAs/dcjsonslas.h"
#include "DartsController/DCMetaSLAs/dcmetaslas.h"
#include "DartsController/DCInputSLAs/dcinputsslas.h"
#include "DartsController/DCInputStatsSLAs/dcinputstatsslas.h"

#define TOURNAMENT_ID_JSON_KEY "tournamentId"

class DartsController : public AbstractDartsController,
                        protected DCMetaSLAs,
                        protected DCTurnvaluesSLAs,
                        protected DCJsonSLAs,
                        protected DCScoreSLAs,
                        protected DCPlayerSLAs,
                        protected DCInputsSLAs,
                        protected DCIndexSLAs,
                        protected DCInputStatsSLAs
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
    void persistInput(const DCInput &input) override;
    void nullifyAndPersistInput(DCInput &input) override;
    void declareWinner(const DCInput &input) override;
private:
    void updateTotalScore(DCInput &input);
    void createAndSendWinnerValues();
    void sendCurrentTurnValues();
};
#endif // FIVEHUNDREDANDONEGAME_H
