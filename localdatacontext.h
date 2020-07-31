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
        PlayerDeleted = 0x26
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    enum ControllerRequest{
        RequestBasicValues = 0x30,
        RequestIndexValues = 0x31,
        RequestPlayerScores = 0x3A,
        RequestSubmitPoint = 0x32,
        RequestAddRound = 0x33,
        RequestAddSet = 0x34
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
    void handleCreateTournamentRequest(const QString &title,
                          const int &numberOfThrows,
                          const int &gameMode,
                          const int &keyPoint,
                          const QVariantList &playerIndexes) override;
    void handleCreatePlayerRequest(const QString &userName, const QString &mail) override;
    void handleDeletePlayerRequest(const int &index) override;
    void handleSendPlayerScoresRequest(const QUuid &tournament)  override;
    void updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex) override;
    void handleAddScoreRequest(const QUuid &tournament,
                  const QString &userName,
                  const int &roundIndex,
                  const int &setIndex,
                  const int &throwIndex,
                  const int &point, const int &score) override;
    void sendRequestedTournaments() override;
    void handleTournamentDetailsRequest(const int &index) override;
    void handleInitialIndexValuesRequest(const QUuid &tournament,const QStringList &assignedPlayers) override;
    void handleSendPlayerDetailsRequest() override;
    void handleControllerStatusRequest(const QUuid &playerID) override;
    /*
     * This method is used in conjunction with the gamecontroller to fullfill the undo/redo functionality
     */
    void setScoreHint(const QUuid &tournament, const QString &player, const int &roundIndex, const int &throwIndex, const int &hint) override;
    void deleteTournamentsFromIndexes(const QVariantList &indexes) override;
    void handlePlayerScoresRequestFromController(const QUuid &tournament, const QVector<QString> &userNames) override;

    void handleRequestFromContext(const int &context, const int &request, const QList<QVariant> &args) override;
    void handleResponseFromContext(const int &context, const int &response, const QList<QVariant> &args) override;
private:

    void createInitialModels();
    /*
     * Persistence related methods
     */
    QJsonArray assembleTournamentsJSONArray();
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
