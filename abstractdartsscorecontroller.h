#ifndef ABSTRACTDARTSSCORECONTROLLER_H
#define ABSTRACTDARTSSCORECONTROLLER_H

#include "abstractdartscontroller.h"

class AbstractDartsScoreController : public AbstractDartsController
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> Player;
    typedef QPair<QUuid,int> PlayerScore;
public slots:
    virtual void initializeControllerPlayerDetails(const QByteArray&) = 0;
    virtual void initializeControllerDartsScores(const QByteArray&) = 0;
    virtual void initializeControllerWinnerIdAndName(const QByteArray&) = 0;
    virtual void assembleMultiAttemptDartsScores() = 0;
    virtual void handleRequestDartsScores() = 0;
    virtual void handleScoreAddedToDataContext(const QByteArray&) = 0;
signals:
    void controllerIsInitializedAndReady();
    void requestAddDartsScore(const QByteArray& tournament);
    void hideDartsScore(const QUuid &tournament,
                        const QUuid &player,
                        const int &roundIndex);
    void revealDartsScore(const QUuid &tournament,
                        const QUuid &player,
                        const int &roundIndex);
    void isReadyAndAwaitsInput(const QByteArray& json);
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
    void sendSingleAttemptDartsScores(const QByteArray& json);
    void sendMultiAttemptDartsScores(const QByteArray& json);
    void controllerIsInitialized();
};



#endif // ABSTRACTDARTSSCORECONTROLLER_H
