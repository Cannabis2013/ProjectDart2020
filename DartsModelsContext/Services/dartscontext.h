#ifndef DARTSCONTEXT_H
#define DARTSCONTEXT_H
#include "DartsModelsContext/SLAs/abstractdtsctx.h"
#include "DartsModelsContext/SLAs/DartsModelsSLAs.h"
class DartsContext : public AbstractDtsCtx,
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
    QByteArray tournament(const int &index) const override;
    QByteArray tournament(const QString &id) const override;
    AbstractDartsTournament * tournament(const QUuid &id) const override;
    bool isConsistent(const QUuid &tournamentId) const override;
    void tryRepair(const QUuid &tournamentId) override;
    bool setTournamentWinner(const QByteArray &json) override;
    QVector<AbstractDartsInput*> inputs(const QUuid &tournamentId) const override;
    AbstractDartsInput *input(const QUuid &tournament, const QString &name, IDartsIndex *index) const override;
    bool addInput(QUuid tournamentId, DIptVals iptVals) override;
    bool hideInput(QUuid tournament, QString name, IDartsIndex *index) override;
    bool revealInput(QUuid tournament, QString name, IDartsIndex *index) override;
    QVector<IPlayerModel *> players(const QUuid &tournamentId) const override;
    bool updateTournamentIndex(QUuid tournament, IDartsIndex *index) override;
    bool resetTournament(const QUuid &tournamentId) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
};
#endif // LOCALMODELSSERVICE_H
