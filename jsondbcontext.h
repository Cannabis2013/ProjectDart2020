#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include "imodelsdbcontext.h"
#include "persistenceinterface.h"
#include "abstractpersistence.h"
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ftptournament.h"
#include "firsttopostscore.h"
#include "abstractjsonpersistence.h"
#include "player.h"

class JsonDbContext :
        public ImodelsDBContext,
        public AbstractJSONPersistence
{
public:
    // Public types
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    JsonDbContext()
    {
        loadIntoMemmory();
    }
    // PersistenceInterface interface
    void loadIntoMemmory() override;
    void saveState() override;
    // ImodelsDBContext interface
    void addTournament(DbModels::TournamentInterface *model) override;
    const DbModels::TournamentInterface *tournamentModel(const int &index) override;
    virtual const DbModels::TournamentInterface *tournamentModel(const QUuid &id) override;
    QVector<const DbModels::TournamentInterface *> tournaments() override;
    void removeTournamentModel(const QUuid &id) override;
    void removeTournamentModel(const int &index) override;
    int indexOfTournament(const DbModels::TournamentInterface *model) override;
    void replaceTournament(const int& index, const DbModels::TournamentInterface* tournament) override;
    void addScoreModel(const DbModels::ScoreInterface *model) override;
    const DbModels::ScoreInterface *scoreModel(const int &index) override;
    QVector<const DbModels::ScoreInterface *> scoreModels() override;
    virtual int indexOfScoreModel(const DbModels::ScoreInterface *score) override;
    virtual void replaceScoreModel(const int &index, const DbModels::ScoreInterface *score) override;
    virtual void removeScoreModel(const int &index) override;
    virtual void addPlayerModel(const DbModels::PlayerInterface *player) override;
    virtual const DbModels::PlayerInterface *playerModel(const int &index) override;
    virtual QVector<const DbModels::PlayerInterface *> playerModels() override;
    virtual void removePlayerModel(const QUuid &id) override;
    virtual void removePlayerModel(const int &index) override;
    virtual int indexOfPlayerModel(const DbModels::PlayerInterface *player) override;
    virtual void replacePlayerModel(const int &index, const DbModels::PlayerInterface *player) override;
private:
    /*
     * Extract models from JSON
     */
    QJsonArray assembleFTPTournamentsJSONArray();
    QJsonArray assembleScoresJSONArray();
    QJsonArray assemblePlayersJSONArray();
    /*
     * Get models from JSON
     */
    void extractTournamentModelsFromJSON(const QJsonArray &arr);
    void extractScoreModelsFromJSON(const QJsonArray &arr);
    void extractPlayerModelsFromJSON(const QJsonArray &arr);


    QVector<const DbModels::TournamentInterface*> _tournamentModels;
    QVector<const DbModels::ScoreInterface*> _scoreModels;
    QVector<const DbModels::PlayerInterface*> _playerModels;
};
#endif // LOCALTOURNAMENTMODELDB_H
