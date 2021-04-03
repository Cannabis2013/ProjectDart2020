#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include <QVariantList>
#include "abstractmodelscontext.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "tournamentbuilder.h"
#include "scorebuilder.h"
#include "playermodelbuilder.h"
#include "jsondbcontext.h"


class LocalModelsContext : public AbstractModelsContext
{
public:
    /*
     * Public types
     */
    enum TournamentModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        ModelsStatePersisted = 0x47
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    /*
     * Destructor
     *  - Delete contexts to persists changes
     */
    ~LocalModelsContext();
    /*
     * Create instance
     */
    static LocalModelsContext* createInstance();
    TournamentModelsContextInterface* tournamentModelsContext() const;
    LocalModelsContext *setTournamentModelsContext(TournamentModelsContextInterface* tournamentModelsContext);

    PlayerModelsContextInterface* playerModelsContext() const;
    LocalModelsContext *setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext);
public slots:
    /*
     * General tournaments methods
     */
    void assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void deleteTournaments(const QVector<int>&indexes) override;
    void handleRequestAssignedPlayers(const QUuid &tournament) override;
    void handleRequestGameMode(const int &index) override;
    void handleRequestTournaments() override;
    void resetTournament(const QUuid &tournament) override;
    /*
     * First To Post tournaments methods
     */
    void addFTPTournament(const QString &title,
                                  const QVector<int> &data,
                                  const QVector<int> &assignedPlayerIndexes) override;
    void handleRequestFtpScores(const QUuid &tournament) override;
    /*
     * Handle request for 'first To Post'-tournament related meta information
     * from frontend
     *
     * Returned data structure:
     *  - String values are placed in a list of strings
     *  | in the following locations:
     *      [0] = Tournament title
     *      [1] = Tournament winner name
     *  - Numeric values are placed in a list of integers
     *  | in the following locations:
     *      [0] = Tournmaent game mode
     *      [1] = Tournament keypoint
     *      [2] = Tournament model tablehint
     *      [3] = Tournament input mode
     */
    void assembleFTPMetaDataFromId(const QUuid& tournament) override;
    void addFtpScore(const QUuid &tournament,
                        const QUuid &player,
                        const int& roundIndex,
                        const int& setIndex,
                        const int& attemptIndex,
                        const int& point,
                        const int& score,
                        const int& keyCode,
                        const bool &isWinnerDetermined) override;
    void setFtpScoreHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &attemptIndex,
                                               const int &hint) override;
    /*
     * Send tournament values
     */
    void assembleFtpKeyValues(const QUuid& tournament) override;
    /*
     * Assemble First To Post tournament indexes and playerscores
     */
    virtual void assembleFtpIndexesAndScores(const QUuid &tournament) override;
    /*
     * Player models context related methods
     */
    void createPlayer(const QString &name, const QString &mail) override;
    void deletePlayerFromIndex(const int &index) override;

    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;

private:
    TournamentModelsContextInterface* _tournamentModelsContext;
    PlayerModelsContextInterface* _playerModelsContext;
};

#endif // MODELCONTEXTINTERFACE_H
