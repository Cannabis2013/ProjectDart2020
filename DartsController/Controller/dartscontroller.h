#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runlater.h"
#include <JsonUtils/jsonextractor.h>
#include "DartsController/ControllerSLA/controllerslas.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class DartsController : public AbstractDartsController, public ControllerSLAs
{
    Q_OBJECT
    int initialize(const QUuid &tournamentId) override;
    virtual QString tournamentId() const override;
    QByteArray getPlayerScores() override;
    void handleUserInput(const QByteArray &json) override;
    void undoTurn() override;
    void redoTurn() override;
    QByteArray getTurnValuesJson() override;
    void addInputToModelsContext(AbstractDartsInput *input) override;
public slots:
    void reset() override;
private:
    void updateScoreDetails(AbstractDartsInput *input);
    QByteArray createTurnValuesJson();
    QByteArray createWinnerJson();
};
#endif // FIVEHUNDREDANDONEGAME_H
