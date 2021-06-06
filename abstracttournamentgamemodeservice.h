#ifndef ABSTRACTREQUESTCONTROLLERDETAILS_H
#define ABSTRACTREQUESTCONTROLLERDETAILS_H

#include <qobject.h>
#include <quuid.h>
class AbstractTournamentGameModeService : public QObject
{
    Q_OBJECT
public slots:
    virtual void handleTournamentGameMode(const QUuid &tournamentId, const int &gameMode) = 0;

signals:
    void requestDartsDetails(const QUuid &tournamentId);
};

#endif // ABSTRACTREQUESTCONTROLLERDETAILS_H
