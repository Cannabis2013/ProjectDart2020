#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include "abstractmodelscontextinterface.h"
#include "tournamentmodelscontextinterface.h"
#include "playermodelscontextinterface.h"

#include <QVariantList>

class ModelsContextInterface : public AbstractModelsContextInterface
{
public:
    enum TournamentModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        TournamentDetailsFailed
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
    ModelsContextInterface();

    static ModelsContextInterface* createInstance();


    TournamentModelsContextInterface* tournamentModelsContext() const;
    ModelsContextInterface *setTournamentModelsContext(TournamentModelsContextInterface* tournamentModelsContext);

    PlayerModelsContextInterface* playerModelsContext() const;
    ModelsContextInterface *setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext);

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
    void handleRequestForTournamentMetaData(const QUuid &tournament) override;
    void handleAddScore(const QUuid &tournament,
                  const QUuid &player,
                  const QList<int> &dataValues,
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
private:
    TournamentModelsContextInterface* _tournamentModelsContext;
    PlayerModelsContextInterface* _playerModelsContext;
};

#endif // MODELCONTEXTINTERFACE_H
