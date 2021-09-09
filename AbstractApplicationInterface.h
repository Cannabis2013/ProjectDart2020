#ifndef ABSTRACTAPPLICATIONINTERFACE_H
#define ABSTRACTAPPLICATIONINTERFACE_H

#include <qobject.h>
#include <quuid.h>
#include "abstractdartsmodelscontext.h"
#include "abstractdartscontroller.h"
#include "iresponseinterface.h"

class AbstractApplicationInterface :
        public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual void addDartsTournaments(const QByteArray &json) = 0;
public slots:
    // Pure virtual slots
    virtual void handleSendGameModesRequest() const = 0;
    virtual void setDartsController(AbstractDartsController* controller) = 0;
signals:
    /*
     * ApplicationInterface interface
     */
    void requestWakeUp();
    void requestDeleteTournaments(const QVector<int>& indexes);
    void requestTournaments();
    void requestPlayers();
    void sendAssignedPlayerIndexes(const QVariantList &indexes,
                                   const QUuid &tournament);
    void sendRequestedGameModes(const QStringList &gameModes);
    void sendRequestedTournament(const QString &title,
                                 const int &gameMode,
                                 const int &playersCount);
    void sendDartsDetails(const QByteArray& json);
    void sendGameModes(const QStringList &modes) const;
    void sendInitialControllerValues(const QUuid &tournament, const int &keyPoint,
                                     const int &numberOfThrows, QList<QUuid> assignedPlayers);
    void requestOrderedDartsInputs();
    void requestDartsScores();
    void setCurrentActiveTournament(const int &index);
    void requestTournamentReset();
    void requestControllerState();
    void requestUndo();
    void requestRedo();
    void requestCurrentTournamentId();
    void removeScore(const QString &player);
    void sendDartsTournamentData(const QByteArray& json);
    void tournamentsDeletedSuccess(const bool &status);
    void sendTournaments(const QByteArray& json);
    void sendPlayers(const QByteArray& json);
    void tournamentAssembledAndStored();
    void tournamentCreatedOk();
    void sendDartsScores(const QByteArray& json);
    void sendOrderedDartsInputs(const QByteArray& json);
    // Player signals
    void requestCreatePlayer(const QByteArray &json);
    void requestDeletePlayers(const QVector<int> &indexes);
    void createPlayerResponse(const bool &status);
    void playersDeletedStatus(const bool &status);
    // Controller signals
    void addUserInput(const QByteArray& json);
    void requestStartGame();
    void requestStopGame();
    void controllerIsStopped();
    void dartsPointMultiColumnsInitialized();
    void dartsPointSingleColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();
    void dartsControllerRemovedPoint(const QString& json);
    void dartsInputRemoveSucces(const QString& json);
    void dartsControllerIsReady();
    void addedInput(const QByteArray& json);
    void controllerAwaitsInput(const QByteArray& json);
    void dartsControllerIsReset();
    void controllerHasDeclaredAWinner(const QString& json);
    void createDartsController(const QByteArray& json,
                               AbstractApplicationInterface* applicationsInteface,
                               AbstractDartsModelsContext* modelsContextInterface);
};

#endif // ABSTRACTAPPLICATIONINTERFACE_H
