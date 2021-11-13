#ifndef ABSTRACTDARTSCONTROLLER_H
#define ABSTRACTDARTSCONTROLLER_H
#include "DartControllerContext/SLAs/abstractgamecontroller.h"
class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual int initialize(const QUuid &tournamentId, const int &remainingScore) = 0;
    Q_INVOKABLE virtual QByteArray createScores() = 0;
public slots:
    virtual void persistInput(AbstractDartsInput *input) = 0;
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
