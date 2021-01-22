#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <quuid.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include <iostream>
#include <qthread.h>

#include "imodelsdbcontext.h"
#include "itournamentmodelbuilder.h"
#include "modelbuildercontext.h"
#include "ftptournamentmodelinterface.h"
#include "iscoremodel.h"

#include "tournamentmodelscontextinterface.h"
#include "abstractjsonpersistence.h"
#include "persistenceinterface.h"

using namespace std;


class IModelParameter
{
public:
    virtual bool generateID() = 0;
    virtual IModelParameter *setGenerateID(const bool &) = 0;
};

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();



typedef FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString> DefaultTournamentInterface;
typedef IScore<QUuid> DefaultScoreInterface;

typedef ITournamentModelBuilder<DefaultTournamentInterface,
                                FTPParameters,
                                DefaultScoreInterface,
                                FTPScoreParameters,
                                ModelOptions> DefaultTournamentModelBuilder;

class LocalTournamentModelsContext :
        public TournamentModelsContextInterface,
        public AbstractJSONPersistence,
        public PersistenceInterface
{
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
    static LocalTournamentModelsContext *createInstance();
    LocalTournamentModelsContext* setup();

    /*
     * Model builder
     */
    LocalTournamentModelsContext *setModelBuilder(DefaultTournamentModelBuilder *builder);
    DefaultTournamentModelBuilder *modelBuilder();

    /*
     * Tournament related section
     */
    QUuid assembleAndAddFTPTournament(const QString &title,
                                      const QVector<int> &data,
                                      const QVector<QUuid> &playerIds) override;
    bool removeTournament(const QUuid &tournament) override;
    bool removeTournamentsFromIndexes(const QVector<int>& indexes) override;
    QUuid tournamentIdFromIndex(const int &index) override;
    QVector<QUuid> tournaments() override;
    int tournamentsCount() override;
    QString tournamentTitle(const QUuid &tournament) override;
    int tournamentNumberOfThrows(const QUuid &tournament) override;
    QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) override;
    int tournamentGameMode(const QUuid &tournament) override;
    int tournamentLastThrowKeyCode(const QUuid &tournament) override;
    int tournamentKeyPoint(const QUuid &tournament) override;
    int tournamentTableViewHint(const QUuid &tournament) override;
    int tournamentInputMode(const QUuid &tournament) override;
    int tournamentStatus(const QUuid &tournament) override;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) override;
    void setTournamentDeterminedWinner(const QUuid &tournament,
                                       const QUuid &winner) override;
    void assignPlayerToTournament(const QUuid &tournament,
                                  const QUuid &player) override;
    void tournamentRemovePlayer(const QUuid &tournament,
                                const QUuid &player) override;
    /*
     * Scores related section
     */
    void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const QList<int> &dataValues,
                  const bool &isWinnerDetermined) override;
    QUuid playerScore(const QUuid &tournament,
                      const QUuid &player ,
                      const int &round,
                      const int &throwIndex,
                      const int &hint) override;
    QList<QUuid> scores() override;
    QList<QUuid> scores(const QUuid &tournament) override;
    QList<QUuid> scores(const QUuid &tournament,
                        const int &roundID) override;
    QList<QUuid> scores(const QUuid &tournament,
                        const int &roundID,
                        const int &setID) override;
    QList<QUuid> scores(const int &hint,
                        const QUuid &tournament) override;
    QList<QUuid> playerScores(const QUuid &tournament,
                              const QUuid &player,
                              const int &hint) override;
    int playerScoreCount(const int &hint) override;
    QUuid setScoreHint(const QUuid &point,
                       const int &hint) override;
    QUuid editScore(const QUuid &pointId,
                    const int &value,
                    const int &score,
                    const int &hint) override;
    int scoreRoundIndex(const QUuid &playerScore) override;
    int scoreSetIndex(const QUuid &playerScore) override;
    int scoreThrowIndex(const QUuid &playerScore) override;
    int scorePointValue(const QUuid &playerScore) override;
    int scoreValue(const QUuid &point) override;
    QUuid scoreTournament(const QUuid &playerScore) override;
    QUuid scorePlayer(const QUuid &playerScore) override;
    int scoreHint(const QUuid &scoreID) override;
    int scoreKeyCode(const QUuid &scoreID) override;
    bool removeScore(const QUuid &point) override;
    void removePlayerScore(const QUuid &point) override;

    void removeHiddenScores(const QUuid &tournament) override;

    int score(const QUuid &tournament,
              const QUuid &player) override;
    int score(const QUuid &player) override;
    QList<QUuid> pointModels(const QUuid &player) override;
    void removeTournamentScores(const QUuid &tournament) override;
    void removeTournamentModel(const QUuid &tournament) override;
    void removePointModel(const QUuid &playerScore) override;

    /*
     * Tournament indexes
     */
    const QList<int> indexes(const QUuid &tournament) override;
    /*
     * Tournament scores
     */
    QList<int> tournamentUserScores(const QUuid &tournament) override;
    LocalTournamentModelsContext* setModelDBContext(ImodelsDBContext<ModelInterface<QUuid>, QString> *context);
private:
    ImodelsDBContext<ModelInterface<QUuid>,QString>* modelDBContext();
    /*
     * Get tournament model
     */
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

    ImodelsDBContext<ModelInterface<QUuid>,QString>* _dbContext;
};

#endif // TOURNAMENTMODELCONTEXT_H
