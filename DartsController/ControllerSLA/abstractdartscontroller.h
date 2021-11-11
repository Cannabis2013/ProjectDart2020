#ifndef ABSTRACTDARTSCONTROLLER_H
#define ABSTRACTDARTSCONTROLLER_H
#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include <DartsController/DCInputServices/dcinput.h>
class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void createScores() = 0;
    virtual void persistInput(DCInput &input) = 0;
    virtual void createTurnValuesJson() = 0;
signals:
    void sendTurnValues(const QByteArray& json);
    void initialized();
    void controllerAwaitsInput();
    void updateTournamentIndex(const QByteArray &json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void updatePlayerScore(const QByteArray& json);
    void sendDartsScores(const QByteArray& json);
    void sendOrderedInputs(const QByteArray &json);
};
#endif
