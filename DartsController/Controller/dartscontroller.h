#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DartsController/DCIndexSLAs/dcindexslas.h"
#include "DartsController/DCScoresSLAs/dcscoreslas.h"
#include "DartsController/DCPlayerSLAs/DCPlayerSLAs.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartsController/DCJsonSLAs/dcjsonslas.h"
#include "DartsController/DCMetaSLAs/dcmetaslas.h"
#include "DartsController/DCInputSLAs/dcinputsslas.h"
#include "DartsController/PlayerStatsSLAs/dcinputstatsslas.h"
class DartsController : public AbstractDartsController,
                        protected DCMetaSLAs,
                        protected DCTurnvaluesSLAs,
                        protected DCJsonSLAs,
                        protected DCScoreSLAs,
                        protected DCPlayerSLAs,
                        protected DCInputsSLAs,
                        protected DCIndexSLAs,
                        protected PlayerStatsSLAs
{
    Q_OBJECT
public slots:
    void beginInitialize() override;
    void initializeDartsValues(const QByteArray &indexJson, const QByteArray &inputsJson,
                               const QByteArray &playersJson, const QByteArray &winnerJson) override;
    virtual void requestStatus() override;
    void createIndexJson() override;
    void undoTurn() override;
    void redoTurn() override;
    void sendTournamentId() override;
    void createScores() override;
    void getOrderedInputsWithTotalScores() override;
    void createJsonResponse() override;
    void handleUserInput(const QByteArray &json) override;
    void reset() override;
    void persistInput(DCInput &input) override;
    void createScoreJson(const QByteArray& json) override;
    void createTurnValuesJson() override;
private:
    void createWinnerJson();
};
#endif // FIVEHUNDREDANDONEGAME_H
