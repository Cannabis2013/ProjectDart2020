#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "DartsController/StaticInitHelperClass/dcinit.h"
#include "AsyncUtils/runlater.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/ControllerSLA/absdartsctrl.h"
class DartsController : public AbsDartsCtrl
{
    Q_OBJECT
public:
    int initialize(const QUuid &tournamentId) override;
    QString tournamentId() const override{return metaCtx()->tournamentId().toString(QUuid::WithBraces);}
    QByteArray getPlayerScores() const override {return createJson()->create(playersContext()->players(),statsContext()->stats());}
    QByteArray addInput(const QByteArray &json) override;
    QByteArray undoTurn() override;
    QByteArray redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override {return createJson()->create(createMeta()->winnerMeta());}
    bool reset() override;
    int status() const override {return metaCtx()->status();}
};
#endif // FIVEHUNDREDANDONEGAME_H
