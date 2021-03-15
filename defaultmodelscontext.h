#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include <QVariantList>
#include "abstractmodelscontext.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "tournamentmodelbuilder.h"
#include "playermodelbuilder.h"
#include "defaultmodelsdbcontext.h"


class DefaultModelsContext : public AbstractModelsContext
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
    enum PlayerContextResponse{
        PlayerCreatedOK = 0x33,
        PlayerDeletedOK = 0x34,
        PlayersDeletedOK = 0x36,
        InconsistencyDetected = 0x39
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    /*
     * Destructor
     *  - Delete contexts to persists changes
     */
    ~DefaultModelsContext();
    /*
     * Create instance
     */
    static DefaultModelsContext* createInstance();



    TournamentModelsContextInterface* tournamentModelsContext() const;
    DefaultModelsContext *setTournamentModelsContext(TournamentModelsContextInterface* tournamentModelsContext);

    PlayerModelsContextInterface* playerModelsContext() const;
    DefaultModelsContext *setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext);
public slots:
    /*
     * Tournament models context interface..
     */
    /*
     * Handle requests from external context
     */
    void handleRequestForAddFTPTournament(const QString &title,
                                  const QVector<int> &data,
                                  const QVector<int> &assignedPlayerIndexes) override;
    void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void handleDeleteTournaments(const QVector<int>&indexes) override;
    void handleRequestAssignedPlayers(const QUuid &tournament) override;
    void handleTransmitPlayerScores(const QUuid &tournament) override;
    void handleTransmitTournamentData() override;
    void handleRequestTournamentGameMode(const int &index) override;
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
    void assembleTournamentMetaDataFromId(const QUuid& tournament) override;
    void handleAddScore(const QUuid &tournament,
                  const QUuid &player,
                  const QVector<int> &dataValues,
                  const bool &isWinnerDetermined) override;
    // Done
    void handleRequestSetScoreHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &throwIndex,
                                               const int &hint) override;
    void handleResetTournament(const QUuid &tournament) override;
    /*
     * Send tournament values
     */
    void handleRequestFTPDetails(const QUuid& tournament) override;
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
