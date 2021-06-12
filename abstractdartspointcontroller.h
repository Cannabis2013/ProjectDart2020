#ifndef ABSTRACTDARTSPOINTCONTROLLER_H
#define ABSTRACTDARTSPOINTCONTROLLER_H

#include <qobject.h>
#include <quuid.h>
#include "abstractdartscontroller.h"

class AbstractDartsPointController : public
        AbstractDartsController
{
    Q_OBJECT
public slots:
    virtual void initializeControllerDartsPoints(const QByteArray&) = 0;
    virtual void handleRequestDartsPoints() = 0;
    virtual void handlePointAddedToDataContext(const QByteArray& json) = 0;
signals:

    void hideDartsPoint(const QUuid &tournament,
                        const QUuid &player,
                        const int &roundIndex,
                        const int &throwIndex);
    void revealDartsPoint(const QUuid &tournament,
                               const QUuid &player,
                               const int &roundIndex,
                               const int &throwIndex);
    void requestDartsPoints(const QUuid& tournament);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);
    void requestTournamentAssignedPlayerDetails(const QUuid& tournamentId);
    void requestTournamentDartsPoints(const QUuid& tournamentId);
    void requestAddDartsPoint(const QByteArray& json);
    void pointAddedAndPersisted(const QByteArray& json);
    void pointRemoved(const QString& json);
    void sendSingleAttemptDartsPoints(const QByteArray& json);
    void sendDartsSingleAttemptPoints(const QByteArray& json);
    void requestTournamentWinnerIdAndName( const QUuid& tournamentId);
};

#endif // ABSTRACTDARTSPOINTCONTROLLER_H
