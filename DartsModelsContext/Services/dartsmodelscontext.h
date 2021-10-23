#ifndef DARTSMODELSCONTEXT_H
#define DARTSMODELSCONTEXT_H

#include "DartsModelsContext/SLAs/abstractdartsmodelscontext.h"
#include "DartsModelsContext/DMCInputSLAs/dartsinputslas.h"
#include "DartsModelsContext/TournamentsSLAs/dartstournamentslas.h"
#include "DartsModelsContext/InputsDbSLAs/DartsInputsDbSLAs.h"
#include "DartsModelsContext/IndexesDbSLAs/dartsindexdbslas.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include "DartsModelsContext/IndexesSLAs/dartsindexslas.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"

class DartsModelsContext :
        public AbstractDartsModelsContext,
        protected DartsTournamentSLAs,
        protected DartsInputSLAs,
        protected DartsInputsDbSLAs,
        protected DartsIndexSLAs,
        protected DartsIndexDbSLAs,
        protected DartsTournamentDbSLAs
{
public:
    //Public types
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
public slots:
    //General tournaments methods
    void deleteTournaments(const QVector<int> &indexes) override;
    void getGameMode(const int &index) override;
    void getTournaments() override;
    void resetTournament(const QUuid &tournamentId) override;
    void setDartsTournamentWinner(const QByteArray &json) override;
    //Darts tournaments methods
    void addDartsTournament(const QByteArray &json, const QVector<IModel<QUuid> *> &playerModels) override;
    void createDartsMetaData(const QUuid& tournamentId) override;
    void getPlayerDetails(const QUuid &tournamentId) override;
    void getTournamentWinnerDetails(const QUuid &tournamentId) override;
    //Darts point methods
    void getOrderedInputs(const QUuid &tournamentId) override;
    void addInput(const QByteArray& json) override;
    virtual void updateTournamentIndexes(const QByteArray &json) override;
    void getPlayerInputs(const QUuid &tournamentId) override;
    virtual void getIndexes(const QUuid &tournamentId) override;
    void hideInput(const QByteArray &json) override;
    void revealInput(const QByteArray &json) override;
    void createDartsKeyValues(const QUuid& tournament) override;
};
#endif // LOCALMODELSSERVICE_H
