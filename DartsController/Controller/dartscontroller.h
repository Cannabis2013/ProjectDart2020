#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runnable.h"
#include <JsonUtils/jsonextractor.h>
#include "DartsController/ControllerSLA/controllerslas.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class DartsController : public AbstractDartsController, public ControllerSLAs
{
    Q_OBJECT
    int initialize(const QUuid &tournamentId, const int &remainingScore) override;
    virtual QString tournamentId() const override;
    QByteArray createScores() override;
    void handleUserInput(const QByteArray &json) override;
public slots:
    void requestStatus() override;
    void createIndexJson() override;
    void undoTurn() override;
    void redoTurn() override;
    void sendTournamentId() override;
    void createJsonResponse() override;
    void reset() override;
    void persistInput(AbstractDartsInput *input) override;
    void createTurnValuesJson() override;
private:
    void updateScoreDetails(AbstractDartsInput *input);
    void createWinnerJson();
};
#endif // FIVEHUNDREDANDONEGAME_H
