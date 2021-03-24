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
     * Tournament models context interface..
     */
    /*
     * Handle requests from external context
     */
    void handleAddFTPTournament(const QString &title,
                                  const QVector<int> &data,
                                  const QVector<int> &assignedPlayerIndexes) override;
    void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void handleDeleteTournaments(const QVector<int>&indexes) override;
    void handleRequestAssignedPlayers(const QUuid &tournament) override;
    void handleRequestFTPScores(const QUuid &tournament) override;
    void handleRequestTournaments() override;
    void handleRequestGameMode(const int &index) override;
    /*
     * Handle request for 'first to post'-tournament related meta information
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
    void handleAddScore(const QUuid &tournament,
                  const QUuid &player,
                  const QVector<int> &dataValues,
                  const bool &isWinnerDetermined) override;
    void handleRequestSetScoreHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &throwIndex,
                                               const int &hint) override;
    void handleResetTournament(const QUuid &tournament) override;
    /*
     * Send tournament values
     */
    void handleRequestFtpDetails(const QUuid& tournament) override;
    /*
     * Player models context interface..
     */
    void handleCreatePlayer(const QString &name, const QString &mail) override;
    void handleDeletePlayerFromIndex(const int &index) override;

    void handleDeletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    /*
     * Persist changes at current time of request
     */
    void handleRequestPersistTournamentState() override;
private:
    TournamentModelsContextInterface* _tournamentModelsContext;
    PlayerModelsContextInterface* _playerModelsContext;
};

#endif // MODELCONTEXTINTERFACE_H
