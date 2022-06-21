#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <DartsController/Contracts/Controller/idartsctrl.h>
#include <DartsController/Contracts/Routines/dartscontrollerroutines.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>

class  DartsController :
        public IDartsCtrl,
        public DartsControllerRoutines,
        public DCServices
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
