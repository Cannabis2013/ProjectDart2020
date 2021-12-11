#ifndef DARTSCONTEXT_H
#define DARTSCONTEXT_H
#include "DartsModelsContext/SLAs/absdartsctx.h"
#include "DartsModelsContext/SLAs/DartsModelsSLAs.h"
class DartsContext : public AbsDartsCtx,
                     public DartsCtxSLAs
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    typedef QVector<IModel<QUuid>*> Models;
    bool addTournament(const QByteArray &json, const QVector<int> &playerIndexes) override;
    bool deleteTournaments(const QVector<int> &indexes) override;
    QByteArray tournaments() override;
    QByteArray tournament(const int &idx) const override;
    QByteArray tournament(const QString &id) const override;
    AbstractDartsTournament * tournament(const QUuid &id) const override;
    bool isConsistent(const QUuid &tournamentId) const override;
    bool tryRepair(const QUuid &tournamentId) override;
    bool setTournamentWinner(const QUuid &tournamentId, const QString &name) override;
    QVector<AbstractDartsInput*> inputs(const QUuid &tournamentId) const override;
    AbstractDartsInput *input(const QUuid &tournament, const QString &name, IDartsIndex *index) const override;
    bool addInput(const QUuid &tournamentId, const DIptVals &input) override;
    bool hideInput(QUuid tournament, QString name, IDartsIndex *index) override;
    bool revealInput(QUuid tournament, QString name, IDartsIndex *index) override;
    QVector<IPlayerModel *> players(const QUuid &tournamentId) const override;
    bool updateTournamentIndex(QUuid tournament, IDartsIndex *index) override;
    bool resetTournament(const QUuid &tournamentId) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
};
#endif // LOCALMODELSSERVICE_H
