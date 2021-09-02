#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "abstractgamecontroller.h"

class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void initializeControllerIndexes(const QByteArray&) = 0;
    virtual void undoSuccess(const QByteArray&) = 0;
    virtual void redoSuccess(const QByteArray&) = 0;
    virtual void initializeDartsScores(const QByteArray&) = 0;
    virtual void createOrderedDartsScores() = 0;
    virtual void handleRequestDartsScores() = 0;
    virtual void handleScoreAddedToDataContext(const QByteArray&) = 0;
signals:
    void awaitsInput(const QByteArray& json);
    void requestDartsTournamentIndexes(const QUuid &tournament);
    void controllerInitialized(const int &displayHint);
    void controllerInitializedAndReady();
    void requestAddDartsScore(const QByteArray& tournament);
    void hideInput(const QUuid &tournament,
                        const QUuid &player,
                        const int &roundIndex,
                        const int &attemptIndex);
    void revealInput(const QUuid &tournament,
                        const QUuid &player,
                        const int &roundIndex,
                          const int &attemptIndex);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);
    void requestDartsScores(const QUuid &tournament);
    void scoreAddedSuccess(const QByteArray& json);
    void scoreRemoved(const QString& json);
    void requestTournamentAssignedPlayerDetails(const QUuid& tournamentId);
    void requestTournamentDartsScores(const QUuid& tournamentId);
    void requestTournamentWinnerIdAndName( const QUuid& tournamentId);
    void sendDartsScores(const QByteArray& json);

};
#endif // FTPCONTROLLER_H
