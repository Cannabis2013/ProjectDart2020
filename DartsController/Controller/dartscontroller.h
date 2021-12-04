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
    QString tournamentId() const override{return metaContext()->tournamentId().toString(QUuid::WithBraces);}
    QByteArray getPlayerScores() const override {return createJson()->create(playersContext()->players(),statsContext()->stats());}
    QByteArray addInput(const QByteArray &json) override;
    QByteArray undoTurn() override;
    QByteArray redoTurn() override;
    QByteArray getTurnValues() const override {return createJson()->create(turnValuesBuilder()->turnValues());}
    QByteArray getWinnerJson() const override {return createJson()->create(createMeta()->winnerMeta());}
    bool reset() override;
    int status() const override {return metaContext()->status();}
};
#endif // FIVEHUNDREDANDONEGAME_H
