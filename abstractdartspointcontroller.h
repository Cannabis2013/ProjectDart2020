#ifndef ABSTRACTDARTSPOINTCONTROLLER_H
#define ABSTRACTDARTSPOINTCONTROLLER_H

#include <qobject.h>
#include <quuid.h>
#include "abstractdartscontroller.h"

class AbstractDartsPointController : public
        AbstractDartsController
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> Player;
    typedef QPair<QUuid,int> PlayerScore;
public slots:
    virtual void assembleSingleAttemptDartsPoints() = 0;
    virtual void handleRequestDartsPoints() = 0;
signals:
    void hideDartsPoint(const QUuid &tournament,
                             const QUuid &player,
                             const int &roundIndex,
                             const int &throwIndex);
    void revealDartsInputPoint(const QUuid &tournament,
                               const QUuid &player,
                               const int &roundIndex,
                               const int &throwIndex);
    void requestDartsPoints(const QUuid& tournament);
    void isReadyAndAwaitsInput(const QString& json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);

    void requestAddDartsPoint(const QByteArray& json);
    void pointAddedAndPersisted(const QByteArray& json);
    void pointRemoved(const QString& json);
    void requestDartsIndexesAndPoints(const QUuid &tournament);
    void sendSingleAttemptDartsPoints(const QByteArray& json);
    void sendMultiAttemptDartsPoints(const QByteArray& json);
};

#endif // ABSTRACTDARTSPOINTCONTROLLER_H
