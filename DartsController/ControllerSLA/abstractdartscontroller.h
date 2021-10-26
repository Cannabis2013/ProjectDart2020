#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include <DartsController/DCInputServices/dcinput.h>

class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void initializeDartsValues(const QByteArray &indexJson, const QByteArray &inputsJson,
                                       const QByteArray &playersJson, const QByteArray &winnerJson) = 0;
    virtual void undoSuccess(const QByteArray&) = 0;
    virtual void redoSuccess(const QByteArray&) = 0;
    virtual void createScores() = 0;
    virtual void getOrderedInputsWithTotalScores() = 0;
    virtual void userInputAdded(const QByteArray& json) = 0;
    virtual void persistInput(DCInput &input) = 0;
signals:
    void sendTurnValues(const QByteArray& json);
    void sendDartsValues(const QUuid &tournament);
    void initialized(const int &inputHint);
    void controllerAwaitsInput();
    void controllerInitializedAndReady();
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
    void scoreAddedSuccess(const QByteArray& json);
    void scoreRemoved(const QString& json);
    void sendDartsScores(const QByteArray& json);
    void requestOrderedInputs(const QUuid &tournament);
    void sendOrderedInputs(const QByteArray &json);
};
#endif
