#ifndef DARTSCONTEXT_H
#define DARTSCONTEXT_H
#include "SLAs/abstractdartscontext.h"
#include "SLAs/dartsmodelsroutines.h"

#ifdef DartsCtxLib
   #define LIB_EXPORT Q_DECL_EXPORT
#else
    #define LIB_EXPORT Q_DECL_IMPORT
#endif
class LIB_EXPORT DartsContext : public AbstractDartsContext,
                                public DartsModelsServices,
                                public DartsModelsRoutines
{
public:
    typedef QVector<IModel<QUuid>*> Models;
    bool addTournament(const QByteArray &json, const QVector<int> &playerIndexes) override;
    bool deleteTournaments(const QVector<int> &indexes) override;
    QByteArray tournaments() override;
    QByteArray tournament(const int &index) const override;
    QByteArray tournament(const QString &id) const override;
    QByteArray tournament(const QUuid &id) const override;
    bool isConsistent(const QUuid &tournamentId) const override;
    bool tryRepair(const QUuid &tournamentId) override;
    bool setTournamentWinner(const QUuid &tournamentId, const QString &name) override;
    QByteArray inputs(const QUuid &tournamentId) const override;
    QByteArray input(const QUuid &tournament, const QString &name, const QByteArray &indexByteArray) const override;
    bool addInput(const QUuid &tournamentId, const QByteArray &inputAsByteArray, const QByteArray &indexByteArray) override;
    bool hideInput(QUuid tournament, QString name, const QByteArray &indexByteArray) override;
    bool revealInput(QUuid tournamentID, QString name, const QByteArray &indexByteArray) override;
    bool resetTournament(const QUuid &tournamentId) override;
    QByteArray createDartsMetaData(const QUuid& tournamentID) override;
};
#endif // LOCALMODELSSERVICE_H
