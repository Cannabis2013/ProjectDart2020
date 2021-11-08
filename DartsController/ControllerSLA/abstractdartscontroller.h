#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include <DartsController/DCInputServices/dcinput.h>

class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void init(const QByteArray &indexJson, const QByteArray &inputsJson,
                                       const QByteArray &playersJson, const QByteArray &winnerJson) = 0;
    virtual void createScores() = 0;
    virtual void createScoreJson(const QByteArray& json) = 0;
    virtual void persistInput(DCInput &input) = 0;
    virtual void createTurnValuesJson() = 0;
signals:
    void sendTurnValues(const QByteArray& json);
    void sendInitValues(const QUuid &tournament);
    void initialized(const int &inputHint);
    void controllerAwaitsInput();
    void addInputToDbContext(const QByteArray& tournament);
    void updateTournamentIndex(const QByteArray &json);
    void hideInput(const QByteArray &json);
    void revealInput(const QByteArray &json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);
    void updatePlayerScore(const QByteArray& json);
    void sendDartsScores(const QByteArray& json);
    void requestOrderedInputs(const QUuid &tournament);
    void sendOrderedInputs(const QByteArray &json);
};
#endif
