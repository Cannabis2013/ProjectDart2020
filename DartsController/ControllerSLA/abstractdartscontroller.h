#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "DartControllerContext/SLAs/abstractgamecontroller.h"

class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void initializeControllerIndexes(const QByteArray&) = 0;
    virtual void undoSuccess(const QByteArray&) = 0;
    virtual void redoSuccess(const QByteArray&) = 0;
    virtual void initializeScores(const QByteArray&) = 0;
    virtual void createDartsScores() = 0;
    virtual void getOrderedInputsWithTotalScores() = 0;
    virtual void handleUserInputAdded(const QByteArray& json) = 0;
    virtual void handleIndexesUpdated(const QByteArray& json) = 0;
    virtual void handleOrderedInputs(const QByteArray &json) = 0;
signals:
    void awaitsInput(const QByteArray& json);
    void requestDartsTournamentIndexes(const QUuid &tournament);
    void initialized(const int &inputHint,const int &displayHint);
    void controllerAwaitsInput();
    void controllerInitializedAndReady();
    void requestAddDartsScore(const QByteArray& tournament);
    void hideInput(const QByteArray &json);
    void revealInput(const QByteArray &json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void sendCurrentIndexes(const QByteArray &json);
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
