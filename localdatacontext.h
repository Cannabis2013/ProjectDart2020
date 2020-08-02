#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H


#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "abstractpersistence.h"
#include "abstractdatacontext.h"

#include "abstractjsonpersistence.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


class LocalDataContext :
        public AbstractDataContext,
        public AbstractJSONPersistence
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    enum ContextStatus{
        ContextBusy = 0xC,
        ContextReady = 0xD
    };
    enum DataContextResponse{
        UpdateSuccessfull = 0xE,
        UpdateUnSuccessfull = 0xF,
        DataRequestSuccess = 0x38,
        DataRequestFailed = 0x39,
        TournamentAdded = 0x23,
        TournamentDeleted = 0x24,
        PlayerAdded = 0x25,
        PlayerDeleted = 0x26,
        EndOfTransmission = 0x41
    };
    enum DataContextRequests{
        RequestCurrentTournament = 0x3B
    };

    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    enum ControllerResponse{
        ScoreTransmit = 0x27,
        ScoreRemove = 0x28,
        InconsistencyDetected = 0x29,
        isInitializedAndWaitsRequest = 0x2D,
        DataProvidedSuccess =0x3D
    };
    enum ControllerRequest{
        RequestBasicValues = 0x30,
        RequestIndexValues = 0x31,
        RequestPlayerScores = 0x3A,
        RequestStorePoint = 0x32,
        RequestUpdateModelState,
        RequestAddRound = 0x33,
        RequestAddSet = 0x34,
        RequestSetModelHint = 0x3C,
        RequestResetTournament = 0x3B
    };
    enum ContextCodes{
        DataContext = 0x35,
        ControllerContext = 0x36,
        ApplicationContext = 0x37
    };
    /*
     * Constructor
     * Destructor
     */
    LocalDataContext(DefaultDataInterface *tournamentModelsContext, PlayerContextInterface *playerModelsContext);
    ~LocalDataContext();
    /*
     * PersistenceInterface interface
     */
    void read() override;
    void write() override;

public slots:
    /*
     * The following slots are called directly from the presentation layer
     */
    void handleCreateTournamentRequest(const QString &title,
                                       const int &numberOfThrows,
                                       const int &gameMode,
                                       const int &winCondition,
                                       const int &keyPoint,
                                       const QVariantList &playerIndexes) override;
    void handleCreatePlayerRequest(const QString &playerName, const QString &mail) override;
    void handleDeletePlayerRequest(const int &index) override;

    void handlePlayerScoresRequest() override;
    void handleTournamentsRequest() override;
    void handleSendPlayerDetailsRequest() override;
    void deleteTournamentsFromIndexes(const QVariantList &indexes) override;

    /*
     * The following two slots is called from controller context
     */
    void handleRequestFromContext(const int &request, const QList<QVariant> &args) override;
    void handleResponseFromContext(const int &response, const QList<QVariant> &args) override;

private:
    /*
     * This method is used in conjunction with the gamecontroller to fullfill the undo/redo functionality
     */
    void setScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex, const int &throwIndex, const int &hint);

    void handleTournamentDetailsRequest(const int &index);
    void handleInitialIndexValuesRequest(const QUuid &tournament,const QStringList &assignedPlayers);

    /*
     * Transmit the following values related to given tournament to UI:
     *  - Tournament keypoint
     *  - Tournament usernames
     *  - Tournament player scores
     */
    void transmitPlayerScores(const QUuid &tournament);
    /*
     * Calculate score for each username provided by the calling context and returns an array of ints
     */
    void sendUserNameScores(const QUuid &tournament, const QStringList &userNames);

    void updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex) override;
    void createInitialModels();
    /*
     * Persistence related methods
     */ QJsonArray assembleTournamentsJSONArray();
    QJsonArray assembleRoundsJSONArray();
    QJsonArray assembeSetsJSONArray();
    QJsonArray assembleScoresJSONArray();
    QJsonArray assemblePlayersJSONArray();

    void extractTournamentModelsFromJSON(const QJsonArray &arr);
    void extractRoundModelsFromJSON(const QJsonArray &arr);
    void extractSetModelsFromJSON(const QJsonArray &arr);
    void extractScoreModelsFromJSON(const QJsonArray &arr);
    void extractPlayerModelsFromJSON(const QJsonArray &arr);

    QStringList playerUserNamesFromPlayersID(const QList<QUuid> playersID);

    int _currentStatus;
    const int _contextCode = 0x1;

};

#endif // LOCALDATACONTEXT_H
