#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "abstractgamecontroller.h"

/*
 * This class is more like a signal interface that ftp based tournaments derive
 */


class AbstractFtpController : public AbstractGameController
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> Player;
    typedef QPair<QUuid,int> PlayerScore;
public slots:
    virtual void assembleSingleAttemptFtpScores() = 0;
    virtual void handleRequestFtpPlayerScores() = 0;
    virtual void recieveFtpIndexesAndEntities(const int& totalTurns,
                                              const int& turns,
                                              const int& roundIndex,
                                              const int& setIndex,
                                              const int& attemptIndex,
                                              const QVector<Player>&,
                                              const QVector<PlayerScore>&) = 0;
signals:
    void isReadyAndAwaitsInput(const QString& json);
    void requestFtpDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);
    void requestFtpMultiAttemptScores(const QUuid &tournament);
    void requestAddFtpScore(const QUuid &tournamentId,
                         const QUuid &playerID,
                         const int& roundIndex,
                         const int& setIndex,
                         const int& attemptIndex,
                         const int& point,
                         const int& score,
                         const int& keyCode,
                         const bool &isWinnerDetermined);
    void scoreAddedAndPersisted(const QString& json);
    void scoreRemoved(const QString& json);
    void requestFtpIndexesAndScores(const QUuid &tournament);
    void sendSingleAttemptFtpScores(const QString& json);
    void propagateFtpMultiAttemptScores(const QString& scores);
};

#endif // FTPCONTROLLER_H
