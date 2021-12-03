#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runlater.h"
#include <JsonUtils/jsonextractor.h>
#include "DartsController/ControllerSLA/ctrlslas.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/StaticInitHelperClass/dcresetcontexts.h"
class DartsController : public AbstractDartsCtrl, public CtrlSLAs
{
    Q_OBJECT
public:
    int initialize(const QUuid &tournamentId) override;
    virtual QString tournamentId() const override;
    QByteArray getPlayerScores() const override;
    QByteArray addInput(const QByteArray &json) override;
    QByteArray undoTurn() override;
    QByteArray redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override;
    bool reset() override;
    virtual int status() const override;
    QByteArray addInputToModelsContext(DCIptVals &input) override;
private:
    void updateScoreDetails(const DCIptVals &input);
};
#endif // FIVEHUNDREDANDONEGAME_H
