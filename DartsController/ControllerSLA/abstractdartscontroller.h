#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include <DartsController/DCInputServices/dcinput.h>

class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void initializeControllerIndexes(const QByteArray&) = 0;
    virtual void undoSuccess(const QByteArray&) = 0;
    virtual void redoSuccess(const QByteArray&) = 0;
    virtual void initializePlayerScores(const QByteArray&) = 0;
    virtual void createScores() = 0;
    virtual void getOrderedInputsWithTotalScores() = 0;
    virtual void userInputAdded(const QByteArray& json) = 0;
    virtual void handleOrderedInputs(const QByteArray &json) = 0;
    virtual void persistInput(DCInput &input) = 0;
    virtual void nullifyAndPersistInput(DCInput &input) = 0;
    virtual void declareWinner(DCInput &input) = 0;
signals:
    void sendTurnValues(const QByteArray& json);
    void requestDartsTournamentIndexes(const QUuid &tournament);
    void initialized(const int &inputHint,const int &displayHint);
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
    void requestTournamentAssignedPlayerDetails(const QUuid& tournamentId);
    void requestScores(const QUuid& tournamentId);
    void requestWinnerDetails( const QUuid& tournamentId);
    void sendDartsScores(const QByteArray& json);
    void requestOrderedInputs(const QUuid &tournament);
    void sendOrderedInputs(const QByteArray &json);
};
#endif
