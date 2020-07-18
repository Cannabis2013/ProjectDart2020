#ifndef ABSTRACTDATACONTEXT_H
#define ABSTRACTDATACONTEXT_H

#include <qobject.h>

#include "idatacontext.h"
#include "modelbuildercollection.h"

#include "iplayerbuildercontext.h"
#include "iplayermodel.h"

#include "istatusinterface.h"

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;

typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder,DefaultPlayerBuilder> DefaultDataInterface;

class AbstractDataContext : public QObject,
        public IStatusInterface<QVariantList>
{
    Q_OBJECT
    enum Status{DataContextReady, DataContextBusy, DataContextFailedToUpdate};
public slots:
    virtual void appendRound(const QUuid &tournament, const int &index) = 0;
    virtual void appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual void addScore(const QUuid &tournament,
                           const QUuid &player,
                           const int &roundIndex,
                           const int &setIndex,
                           const int &legIndex,
                           const int &point) = 0;
    virtual void sendPlayerScores(const QUuid &tournament) = 0;
signals:
    void stateChanged(const int &status);

    void sendPlayerScore(const QString &playerName, const int &score);
    void sendInitialControllerValues(const QUuid &tournamentID,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     QList<QUuid> players);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);

    void sendStatus(const int &status, const QVariantList &args);


};

#endif // ABSTRACTDATACONTEXT_H
