#ifndef ABSDARTSCTX_H
#define ABSDARTSCTX_H
#include <qobject.h>
#include "TournamentsSLAs/dartsslas.h"
#include "InputSLAs/dartsiptslas.h"
#include "IndexesSLAs/dartsindexslas.h"
#include "TournamentsDbSLAs/persistenceslas.h"
class IDartsIndex;
class IDartsInput;
class IPlayer;
class IDartsTournament;
class AbsPlaCtx;
class AbsDartsCtx : public QObject, public DartsSLAs, public DartsIptSLAs,
                    public DartsIndexSLAs, public PersistenceSLAs
{
    Q_OBJECT
public:
    AbsDartsCtx(AbsPlaCtx *plaCtx): _playersContext(plaCtx){}
    virtual ~AbsDartsCtx() = default;
    AbsPlaCtx *playersContext() const {return _playersContext;}
    Q_INVOKABLE virtual QByteArray tournaments() = 0;
    Q_INVOKABLE virtual QByteArray tournament(const int &index) const = 0;
    Q_INVOKABLE virtual QByteArray tournament(const QString &id) const = 0;
    Q_INVOKABLE virtual bool isConsistent(const QUuid &tournamentId) const = 0;
    Q_INVOKABLE virtual bool tryRepair(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual bool deleteTournaments(const QVector<int> &indexes) = 0;
    Q_INVOKABLE virtual bool addTournament(const QByteArray& json, const QVector<int> &playerIndexes) = 0;
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual bool setTournamentWinner(const QUuid &tournamentId, const QString &name) = 0;
    virtual QByteArray tournament(const QUuid &id) const = 0;
    virtual bool resetTournament(const QUuid &tournamentId) = 0;
    virtual QByteArray input(const QUuid &tournament, const QString &name, const QByteArray &indexByteArray) const = 0;
    virtual QByteArray inputs(const QUuid &tournamentId) const = 0;
    virtual bool addInput(const QUuid &tournamentId, const QByteArray &byteArray) = 0;
    virtual bool hideInput(QUuid tournament, QString name, const QByteArray &indexByteArray) = 0;
    virtual bool revealInput(QUuid tournament, QString name, const QByteArray &indexByteArray) = 0;
    virtual bool updateTournamentIndex(QUuid tournament, const QByteArray &indexByteArray) = 0;
private:
    AbsPlaCtx *_playersContext;
};
#endif // ABSDARTSCTX_H
