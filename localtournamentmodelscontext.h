#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <quuid.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include "abstracttournamentmodelscontext.h"
#include "abstractjsonpersistence.h"

#include <iostream>

#include <qthread.h>

using namespace std;


#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


class LocalTournamentModelsContext :
        public AbstractTournamentModelsContext,
        public AbstractJSONPersistence
{
Q_OBJECT

public:
    /*
     * Public types
     */
    enum ModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        TournamentDetailsFailed
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    /*
     * AbstractJSONPersistence interface
     */
    void read() override;
    void write() override;
    /*
     * Destructor
     */
    ~LocalTournamentModelsContext();
    /*
     * Create and setup instance
     */
    static AbstractTournamentModelsContext* createInstance();
    AbstractTournamentModelsContext *setup() override;

    /*
     * Model builder
     */
    AbstractTournamentModelsContext *setModelBuilder(DefaultTournamentModelBuilder *builder) override;
    DefaultTournamentModelBuilder *modelBuilder() override;
    /*
     * Handle requests from external context
     */
    void assembleAndAddTournament(const QString &title,
                                  const QList<int> &data,
                                  const QList<QUuid> &assignedPlayersID) override;
    void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void deleteTournaments(const QVector<int>&indexes) override;
    void handleRequestAssignedPlayers(const QUuid &tournament) override;
    void handleTransmitPlayerScores(const QUuid &tournament,
                                    const QList<QPair<QUuid, QString> > &playerPairs) override;
    void handleTransmitTournaments() override;
    void handleRequestForTournamentMetaData(const QUuid &tournament) override;
    void handleRequestTournamentDetails(const int &index) override;
    void handleRequestTournamentIndexes(const QUuid &tournament) override;
    void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const QList<int> &dataValues,
                  const bool &isWinnerDetermined) override;
    void handleRequestSetScoreHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &throwIndex,
                                               const int &hint) override;
    void handleResetTournament(const QUuid &tournament) override;
    ImodelsDBContext<IModel<QUuid>, QString> *modelDBContext() const;
    AbstractTournamentModelsContext *setModelDBContext(ImodelsDBContext<IModel<QUuid>, QString> *context) override;

private:
    /*
     * Tournament related section
     */
    QUuid createTournament(const QString &title,
                           const QList<int> &data);
    void removeTournament(const QUuid &tournament);
    void removeModelsRelatedToTournament(const QUuid &tournament);
    QUuid tournamentIDFromIndex(const int &index);
    QList<QUuid> tournaments();
    int tournamentsCount();
    QString tournamentTitle(const QUuid &tournament);
    int tournamentNumberOfThrows(const QUuid &tournament);
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament);
    int tournamentGameMode(const QUuid &tournament);
    int tournamentLastThrowKeyCode(const QUuid &tournament);
    int tournamentKeyPoint(const QUuid &tournament);
    int tournamentTableViewHint(const QUuid &tournament);
    int tournamentInputMode(const QUuid &tournament);
    int tournamentStatus(const QUuid &tournament);
    QUuid tournamentDeterminedWinner(const QUuid &tournament);
    void setTournamentDeterminedWinner(const QUuid &tournament, const QUuid &winner);
    void assignPlayerToTournament(const QUuid &tournament, const QUuid &player);
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player);
    /*
     * Scores related section
     */
    QUuid playerScore(const QUuid &tournament, const QUuid &player , const int &round, const int &throwIndex, const int &hint);
    QList<QUuid> scores();
    QList<QUuid> scores(const QUuid &tournament);
    QList<QUuid> scores(const QUuid &tournament, const int &roundID);
    QList<QUuid> scores(const QUuid &tournament, const int &roundID, const int &setID);
    QList<QUuid> scores(const int &hint,const QUuid &tournament);
    QList<QUuid> playerScores(const QUuid &tournament, const QUuid &player, const int &hint);
    int playerScoreCount(const int &hint);
    QUuid setScoreHint(const QUuid &point, const int &hint);
    QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint);
    int scoreRoundIndex(const QUuid &playerScore);
    int scoreSetIndex(const QUuid &playerScore);
    int scoreThrowIndex(const QUuid &playerScore);
    int scorePointValue(const QUuid &playerScore);
    int scoreValue(const QUuid &point);
    QUuid scoreTournament(const QUuid &playerScore);
    QUuid scorePlayer(const QUuid &playerScore);
    int scoreHint(const QUuid &scoreID);
    int scoreKeyCode(const QUuid &scoreID);
    bool removeScore(const QUuid &point);
    void removePlayerScore(const QUuid &point);

    void removeHiddenScores(const QUuid &tournament);

    int score(const QUuid &tournament, const QUuid &player);
    int score(const QUuid &player);
    QList<QUuid> pointModels(const QUuid &player);
    void removeTournamentScores(const QUuid &tournament);
    void removeTournamentModel(const QUuid &tournament);
    void removePointModel(const QUuid &playerScore);

    const DefaultTournamentInterface *getTournamentModelFromID(const QUuid &id);
    const DefaultScoreInterface *getScoreModelFromID(const QUuid &id);
    /*
     * Extract models from JSO
     */
    QJsonArray assembleTournamentsJSONArray();
    QJsonArray assembleScoresJSONArray();

    void extractTournamentModelsFromJSON(const QJsonArray &arr);
    void extractScoreModelsFromJSON(const QJsonArray &arr);
    /*
     * Build and update contextmodel state
     */
    void buildTournament(const QUuid &id,
                         const QString &title,
                         const int &keyPoint, const int &tableViewHint, const int &inputMode,
                         const int &throws,
                         const int &gameMode,
                         const QUuid &winner);
    void buildScoreModel(const QUuid &tournament,
                         const QUuid &player,
                         const QList<int> &dataValues,
                         const int &hint,
                         const bool &generateID = true,
                         const QUuid &id = QUuid());

    DefaultTournamentModelBuilder *_tournamentModelBuilder;

    ImodelsDBContext<IModel<QUuid>,QString> *_dbContext;
};

#endif // TOURNAMENTMODELCONTEXT_H
