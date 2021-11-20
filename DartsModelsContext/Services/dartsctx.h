#ifndef DARTSCTX_H
#define DARTSCTX_H
#include "DartsModelsContext/SLAs/abstractdartsctx.h"
#include "DartsModelsContext/InputSLAs/dartsinputslas.h"
#include "DartsModelsContext/TournamentsSLAs/dartstournamentslas.h"
#include "DartsModelsContext/InputsDbSLAs/DartsInputsDbSLAs.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include "DartsModelsContext/IndexesSLAs/dartsindexslas.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "AsyncUtils/runlater.h"
#include <JsonUtils/jsonbuilder.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class DartsCtx : public AbstractDartsCtx,
                     public DartsTournamentSLAs,
                     public DartsInputSLAs,
                     public DartsInputsDbSLAs,
                     public DartsIndexSLAs,
                     public DartsTournamentDbSLAs
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
    QVector<IModel<QUuid> *> tournamentInputs(const QUuid &tournamentId) const override;
    AbstractDartsInput *input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const override;
    void addInput(const QUuid &tournamentId, AbstractDartsInput *input, std::function<void()> func) override;
    void hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) override;
    void revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) override;
    QVector<IModel<QUuid> *> assignedPlayers(const QUuid &tournamentId) const override;
    QFuture<bool> updateTournamentIndex(const QUuid &tournament, IDartsIndex *index) override;
    QFuture<bool> resetTournament(const QUuid &tournamentId) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
public slots:
};
#endif // LOCALMODELSSERVICE_H
