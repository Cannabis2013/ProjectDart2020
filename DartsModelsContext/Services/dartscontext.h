#ifndef DARTSCONTEXT_H
#define DARTSCONTEXT_H
#include "DartsModelsContext/SLAs/abstractdartscontext.h"
#include "DartsModelsContext/InputSLAs/dartsinputslas.h"
#include "DartsModelsContext/TournamentsSLAs/dartstournamentslas.h"
#include "DartsModelsContext/InputsDbSLAs/DartsInputsDbSLAs.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include <QJsonDocument>
#include <QUuid>
#include <qjsonobject.h>
#include "DartsModelsContext/IndexesSLAs/dartsindexslas.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "AsyncUtils/runnable.h"
#include <JsonUtils/jsonbuilder.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class DartsContext : public AbstractDartsContext,
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
    QByteArray tournaments() override;
    QByteArray tournament(const int &index) const override;
    QByteArray tournament(const QString &id) const override;
    AbstractDartsInput *input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const override;
    QFuture<bool> addInput(const QByteArray& json) override;
    QFuture<bool> hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index) override;
    QFuture<bool> revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index) override;
    QVector<IModel<QUuid> *> assignedPlayers(const QUuid &tournamentId) const override;
    QFuture<bool> updateTournamentIndex(const QUuid &tournament, IDartsIndex *index) override;
    QFuture<bool> resetTournament(const QUuid &tournamentId) override;
public slots:
    void deleteTournaments(const QVector<int> &indexes) override;
    void setTournamentWinner(const QByteArray &json) override;
    void addTournament(const QByteArray &json, const QVector<int> &playerIndexes) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
    QByteArray createDartsValuesJson(const QUuid &tournamentId) override;
    QByteArray createDartsKeyValues(const QUuid& tournament) override;
};
#endif // LOCALMODELSSERVICE_H
