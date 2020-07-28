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
    enum Status{ContextBusy = 0xC,
                ContextReady = 0xD,
                ContextSuccessfullyUpdated = 0xE,
                ContextUnSuccessfullyUpdated = 0xF};
    enum ModelDisplayHint{HiddenHint = 0x9,DisplayHint = 0xA, allHints = 0xB};
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
    void createTournament(const QString &title,
                          const int &numberOfThrows,
                          const int &gameMode,
                          const int &keyPoint,
                          const QVariantList &playerIndexes) override;
    void createPlayer(const QString &userName, const QString &mail) override;
    void handleSendPlayerScoresRequest(const QUuid &tournament)  override;
    void updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex) override;
    void addScore(const QUuid &tournament,
                  const QString &userName,
                  const int &roundIndex,
                  const int &setIndex,
                  const int &throwIndex,
                  const int &point, const int &score) override;
    void sendRequestedTournaments() override;
    void handleSetCurrentTournament(const int &index) override;
    void handleInitialIndexesRequest(const QUuid &tournament,const QVector<QString> &assignedPlayers) override;
    void handleSendPlayerDetailsRequest() override;
    void handleControllerStatusRequest(const QUuid &playerID) override;
    /*
     * This method is used in conjunction with the gamecontroller to fullfill the undo/redo functionality
     */
    void setScoreHint(const QUuid &tournament, const QString &player, const int &roundIndex, const int &throwIndex, const int &hint) override;
    void deleteTournamentsFromIndexes(const QVariantList &indexes) override;
    void handlePlayerScoresRequestFromController(const QUuid &tournament, const QVector<QString> &userNames) override;
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

    QVector<QString> playerUserNamesFromPlayersID(const QList<QUuid> playersID);

    int _currentStatus;
};

#endif // LOCALDATACONTEXT_H
