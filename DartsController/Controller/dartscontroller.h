#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runlater.h"
#include <JsonUtils/jsonextractor.h>
#include "DartsController/ControllerSLA/controllerslas.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/StaticInitHelperClass/dcresetcontexts.h"
class DartsController : public AbstractDartsController, public ControllerSLAs
{
    Q_OBJECT
    int initialize(const QUuid &tournamentId) override;
    virtual QString tournamentId() const override;
    QByteArray getPlayerScores() const override;
    int handleInput(const QByteArray &json) override;
    void addInputToModelsContext(AbstractDartsInput *input) override;
    void undoTurn() override;
    void redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override;
    void reset() override;
    virtual int status() const override;
private:
    void updateScoreDetails(AbstractDartsInput *input);
};
#endif // FIVEHUNDREDANDONEGAME_H
