#ifndef ABSDARTSCTX_H
#define ABSDARTSCTX_H
#include <qobject.h>
#include "DartsModelsContext/TournamentsSLAs/dartsslas.h"
#include "DartsModelsContext/InputSLAs/dartsiptslas.h"
#include "DartsModelsContext/IndexesSLAs/dartsindexslas.h"
#include "DartsModelsContext/InputsDbSLAs/DartsiptDbSLAs.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartsdbslas.h"
class TnmVals;
class IDartsIndex;
class AbstractDartsInput;
class IPlayer;
class AbstractDartsTournament;
class AbsPlaCtx;
class AbsDartsCtx : public QObject,
                    public DartsSLAs,
                    public DartsIptSLAs,
                    public DartsiptDbSLAs,
                    public DartsIndexSLAs,
                    public DartsDbSLAs
{
    Q_OBJECT
public:
    virtual ~AbsDartsCtx() = default;
    AbsPlaCtx *playersContext() const {return _playersContext;}
    void setPlayersContext(AbsPlaCtx *newPlayersContext) {_playersContext = newPlayersContext;}
    Q_INVOKABLE virtual QByteArray tournaments() = 0;
    Q_INVOKABLE virtual QByteArray tournament(const int &index) const = 0;
    Q_INVOKABLE virtual QByteArray tournament(const QString &id) const = 0;
    Q_INVOKABLE virtual bool isConsistent(const QUuid &tournamentId) const = 0;
    Q_INVOKABLE virtual bool tryRepair(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual bool deleteTournaments(const QVector<int> &indexes) = 0;
    Q_INVOKABLE virtual bool addTournament(const QByteArray& json, const QVector<int> &playerIndexes) = 0;
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual bool setTournamentWinner(const QUuid &tournamentId, const QString &name) = 0;
    virtual TnmVals tournament(const QUuid &id) const = 0;
    virtual QVector<IPlayer*> players(const QUuid &tournamentId) const = 0;
    virtual bool resetTournament(const QUuid &tournamentId) = 0;
    virtual DIptVals input(const QUuid &tournament, const QString &name, const TnmVals &index) const = 0;
    virtual bool addInput(const QUuid &tournamentId, const DIptVals &input) = 0;
    virtual bool hideInput(QUuid tournament, QString name, TnmVals index) = 0;
    virtual bool revealInput(QUuid tournament, QString name, const TnmVals &index) = 0;
    virtual QVector<DIptVals> inputs(const QUuid &tournamentId) const = 0;
    virtual bool updateTournamentIndex(QUuid tournament, const TnmVals &index) = 0;
signals:
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedOk();
    void tournamentCreatedFail();
    void sendOrderedInputs(const QByteArray& scores);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeleted();
    void repairCompleted(const bool &status, const QByteArray &json);
private:
    AbsPlaCtx *_playersContext;
};
#endif // ABSDARTSCTX_H
