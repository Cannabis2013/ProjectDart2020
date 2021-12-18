#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H
#include "ControllerSLA/absdartsctrl.h"
#ifdef DARTSCONTROLLERLIB
    #define DCExport Q_DECL_EXPORT
#else
    #define DCExport Q_DECL_IMPORT
#endif
class DCExport DartsController : public AbsDartsCtrl
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
