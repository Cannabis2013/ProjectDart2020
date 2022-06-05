#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "idartsctrl.h"
#include <DartsController/Routines/dartscontrollerroutines.h>
#include <DartsController/ServicesProvider/dcservices.h>


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
