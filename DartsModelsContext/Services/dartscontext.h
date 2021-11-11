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
    void setPlayerModelsContext(PlayerModelsContext *context) override;
public slots:
    void deleteTournaments(const QVector<int> &indexes) override;
    void getTournaments() override;
    QFuture<bool> resetTournament(const QUuid &tournamentId) override;
    void setTournamentWinner(const QByteArray &json) override;
    void addTournament(const QByteArray &json) override;
    QByteArray createDartsMetaData(const QUuid& tournamentId) override;
    QFuture<QByteArray> addInput(const QByteArray& json) override;
    QByteArray createDartsValuesJson(const QUuid &tournamentId) override;
    QFuture<QByteArray> hideInput(const QByteArray &json) override;
    QFuture<QByteArray> revealInput(const QByteArray &json) override;
    QByteArray createDartsKeyValues(const QUuid& tournament) override;
    QFuture<bool> updateTournamentIndex(const QByteArray &json) override;
private:
    AbstractPlayersContext *_playersContext;
};
#endif // LOCALMODELSSERVICE_H
