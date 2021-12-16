#ifndef DARTSCONTEXT_H
#define DARTSCONTEXT_H
#include "DartsModelsContext/SLAs/absdartsctx.h"
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
class DartsContext : public AbsDartsCtx
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
    QByteArray tournaments() override {return tnmJsonBuilder()->create(tnmDbCtx()->models());}
    QByteArray tournament(const int &idx) const override {return tnmJsonBuilder()->create(tnmDbCtx()->model(idx));}
    QByteArray tournament(const QString &id) const override {return tnmJsonBuilder()->create(getTournament()->get(QUuid::fromString(id),tnmDbCtx()));}
    TnmVals tournament(const QUuid &id) const override {return tournamentBuilder()->convert(getTournament()->get(id,tnmDbCtx()));}
    bool isConsistent(const QUuid &tournamentId) const override;
    bool tryRepair(const QUuid &tournamentId) override;
    bool setTournamentWinner(const QUuid &tournamentId, const QString &name) override;
    QVector<DIptVals> inputs(const QUuid &tournamentId) const override;
    DIptVals input(const QUuid &tournament, const QString &name, const TnmVals &index) const override;
    bool addInput(const QUuid &tournamentId, const DIptVals &ctrlIpt) override;
    bool hideInput(QUuid tournament, QString name, TnmVals idxVals) override;
    bool revealInput(QUuid tournament, QString name, const TnmVals &idxVals) override;
    QVector<IPlayer *> players(const QUuid &tournamentId) const override;
    bool updateTournamentIndex(QUuid tournament, const TnmVals &idxVal) override;
    bool resetTournament(const QUuid &tournamentId) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override {return tnmJsonBuilder()->create(getTournament()->get(tournamentId,tnmDbCtx()));}
};
#endif // LOCALMODELSSERVICE_H
