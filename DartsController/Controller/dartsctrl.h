#ifndef DARTSCTRL_H
#define DARTSCTRL_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runlater.h"
#include <JsonUtils/jsonextractor.h>
#include "DartsController/ControllerSLA/ctrlslas.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/StaticInitHelperClass/dcresetcontexts.h"
class DartsCtrl : public AbstractDartsCtrl, public CtrlSLAs
{
    Q_OBJECT
    int initialize(const QUuid &tournamentId) override;
    virtual QString tournamentId() const override;
    QByteArray getPlayerScores() const override;
    int handleInput(const QByteArray &json) override;
    void addInputToModelsContext(DCIptVals &input) override;
    void undoTurn() override;
    void redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override;
    void reset() override;
    virtual int status() const override;
private:
    void updateScoreDetails(const DCIptVals &input);
};
#endif // FIVEHUNDREDANDONEGAME_H
