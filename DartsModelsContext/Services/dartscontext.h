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
    void addTournament(const QByteArray &json, const QVector<int> &playerIndexes) override;
    void deleteTournaments(const QVector<int> &indexes) override;
    QByteArray tournaments() override;
    QByteArray tournament(const int &index) const override;
    QByteArray tournament(const QString &id) const override;
    AbstractDartsTournament * tournament(const QUuid &id) const override;
    bool isConsistent(const QUuid &tournamentId) const override;
    void tryRepair(const QUuid &tournamentId) override;
    void setTournamentWinner(const QByteArray &json) override;
    QVector<AbstractDartsInput*> inputs(const QUuid &tournamentId) const override;
    AbstractDartsInput *input(const QUuid &tournament, const QString &name, IDartsIndex *index) const override;
    void addInput(QUuid tournamentId, DIptVals iptVals, std::function<void()> func) override;
    void hideInput(QUuid tournament, QString name, IDartsIndex *index, std::function<void()> func) override;
    void revealInput(QUuid tournament, QString name, IDartsIndex *index, std::function<void()> func) override;
    QVector<IPlayerModel *> players(const QUuid &tournamentId) const override;
    void updateTournamentIndex(QUuid tournament, IDartsIndex *index, std::function<void()> func) override;
    void resetTournament(const QUuid &tournamentId, std::function<void ()> func) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
};
#endif // LOCALMODELSSERVICE_H
