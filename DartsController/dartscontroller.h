#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#ifdef DARTSCONTROLLERLIB
    #define DartsController_Export Q_DECL_EXPORT
#else
    #define DartsController_Export Q_DECL_IMPORT
#endif
#include "ControllerSLA/absdartsctrl.h"
class DartsController_Export DartsController : public AbsDartsCtrl
{
    Q_OBJECT
public:
    int initialize(const QUuid &tournamentId) override;
    QString tournamentId() const override;
    QByteArray getPlayerScores() const override;
    QByteArray addInput(const QByteArray &json) override;
    QByteArray undoTurn() override;
    QByteArray redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override;
    bool reset() override;
    int status() const override;
};
#endif // FIVEHUNDREDANDONEGAME_H
