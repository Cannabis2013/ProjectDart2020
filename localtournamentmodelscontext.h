#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

#include "imodelsdbcontext.h"
#include "tournamentbuildercontext.h"
#include "tournamentcontextcollection.h"
#include "scorebuildercontext.h"
#include "tournamentmodelscontextinterface.h"
#include "abstractjsonpersistence.h"


#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

class LocalTournamentModelsContext :
        public TournamentModelsContextInterface
{
public:
    /*
     * Public types
     */
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };

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
    LocalTournamentModelsContext *setTournamentBuilder(LMC::ITournamentModelsBuilder *builder);
    LMC::ITournamentModelsBuilder *tournamentBuilder();
    LocalTournamentModelsContext *setScoreBuilder(LMC::IScoreModelsBuilder* builder);
    LMC::IScoreModelsBuilder* scoreBuilder();
    /*
     * Tournament related section
     */
    /*
     * General tournament related
     */
    bool removeTournament(const QUuid &tournament) override;
    bool removeTournamentsFromIndexes(const QVector<int>& indexes) override;
    QUuid tournamentIdFromIndex(const int &index) override;
    QVector<QUuid> tournaments() override;
    int tournamentsCount() override;
    QString tournamentTitle(const QUuid &tournament) override;
    int tournamentStatus(const QUuid &tournament) override;
    QUuid tournamentWinner(const QUuid &tournament) override;
    void tournamentSetWinnerId(const QUuid &tournament,
                                       const QUuid &winner) override;
    QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) override;
    void tournamentAssignPlayer(const QUuid &tournament,
                                  const QUuid &player) override;
    void tournamentUnAssignPlayer(const QUuid &tournament,
                                const QUuid &player) override;
    /*
     * FTP tournament related
     */
    QUuid tournamentAssembleAndAddFTP(const QString &title,
                                      const QVector<int> &data,
                                      const QVector<QUuid> &playerIds) override;
    int tournamentAttempts(const QUuid &tournament) override;
    int tournamentGameMode(const QUuid &tournament) override;
    int tournamentTerminalKeyCode(const QUuid &tournament) override;
    int tournamentKeyPoint(const QUuid &tournament) override;
    int tournamentTableViewHint(const QUuid &tournament) override;
    int tournamentInputMode(const QUuid &tournament) override;
    /*
     * Scores related section
     */
    void addFTPScore(const QUuid &tournament,
                  const QUuid &player,
                  const QVector<int> &dataValues,
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
    int scoreAttemptIndex(const QUuid &playerScore) override;
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
    const QVector<int> indexes(const QUuid &tournament) override;
    /*
     * Tournament scores
     */
    QVector<int> tournamentUserScores(const QUuid &tournament) override;
    LocalTournamentModelsContext* setModelDBContext(ImodelsDBContext* context);
private:
    ImodelsDBContext* modelDBContext();
    /*
     * Get tournament model
     */
    template<typename TModelInterface>
    const TModelInterface *getTournamentModelFromID(const QUuid &id);
    const LMC::ScoreInterface *getScoreModelFromID(const QUuid &id);

    LMC::ITournamentModelsBuilder *_tournamentModelBuilder;
    LMC::IScoreModelsBuilder* _scoreModelbuilder;
    ImodelsDBContext* _dbContext;
};

#endif // TOURNAMENTMODELCONTEXT_H
