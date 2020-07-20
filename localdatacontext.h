#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H


#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "abstractpersistence.h"
#include "abstractdatacontext.h"

#include "localtournamentmodelcontext.h"
#include "localplayermodelcontext.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


class LocalDataContext : public AbstractDataContext,
        private AbstractPersistence
{
    Q_OBJECT
public:
    enum Status{ContextBusy = 0xC,
                ContextReady = 0xD,
                ContextSuccessfullyUpdated = 0xE,
                ContextUnSuccessfullyUpdated = 0xF,
                ContextDataProvided = 0x19};
    enum GameStatus {GameControllerIdle = 0x10,
                     GameControllerBusy = 0x11, // Game is idle but in progress
                     GameControllerStopped = 0x12, // Game is stopped and no longer accepts input
                     GameControllerAwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
                     GameControllerRunning = 0x14,
                     GameControllerWinnerDeclared = 0x15,
                     GameControllerNotInitialized = 0x16, // Controller is not initialized with tournament and, if necessary, appropriate indexes
                     GameControllerInitialized = 0x17,
                     GameControllerNeedsData = 0x18}; // Controller needs data from context
    /*
     * Public types
     */;

    LocalDataContext(const QString &org, const QString &app);

    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};

    void read()  override;
    void write()  override;

public slots:
    void createTournament(const QString &title,
                          const int &numberOfThrows,
                          const int &maxPlayers,
                          const int &gameMode,
                          const int &keyPoint,
                          const QVariantList &playerIndexes) override;
    void createPlayer(const QString &userName, const QString &mail) override;
    void handleSendPlayerScoresRequest(const QUuid &tournament)  override;
    void updateDataContext(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const int &roundIndex,
                  const int &setIndex,
                  const int &legIndex,
                  const int &point, const int &totalScore) override;
    void sendRequestedTournaments() override;
    void handleSetCurrentTournament(const int &index) override;
    void handleInitialIndexesRequest(const QUuid &tournament,const QList<QUuid> *assignedPlayers) override;
    void handleSendPlayerDetailsRequest() override;
    void handleControllerStatusRequest(const QUuid &playerID) override;
    void handleScoreCalculationRequest(const QUuid &tournament, const QUuid &player, const int &point) override;

private:
    void createInitialModels();
    int _currentStatus;
};

#endif // LOCALDATACONTEXT_H
