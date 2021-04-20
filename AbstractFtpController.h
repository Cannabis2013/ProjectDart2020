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
    virtual void initializeController(const QByteArray&) = 0;
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
    void requestAddFtpScore(const QByteArray& json);
    void scoreAddedAndPersisted(const QByteArray& json);
    void scoreRemoved(const QString& json);
    void requestFtpIndexesAndScores(const QUuid &tournament);
    void sendSingleAttemptFtpScores(const QByteArray& json);
    void sendMultiAttemptFtpScores(const QByteArray& json);

};

#endif // FTPCONTROLLER_H
