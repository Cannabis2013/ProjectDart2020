#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>
#include <qthreadpool.h>
#include <iostream>

#include "itournamentmodelbuilder.h"
#include "iplayerbuildercontext.h"
#include "abstractcontrollerbuilder.h"

using namespace std;

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication : public AbstractApplicationInterface
{
    Q_OBJECT
public:

    /*
     * Should be located in an eventual 'ModelsContextBuilder'
     * enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };
     */
    /*
     * Destructor
     */
    ~DartApplication() override;
    /*
     * Create and setup instance
     */
    static DartApplication* createInstance();
    DartApplication *setup();
    DartApplication *useThreads();
    /*
     * Get/set modelcontext interface
     */
    AbstractModelsContextInterface *modelsContextInterface() const;
    DartApplication* setModelsContextInterface(AbstractModelsContextInterface *modelsInterface);
    /*
     * Get/set GameControllerBuilder
     */
    AbstractControllerBuilder* controllerBuilder();
    DartApplication *setControllerBuilder(ControllerBuilder *builder);

public slots:
    void handleTournamentsRequest() override;
    /*
     * Set current tournament
     */
    void handleSetCurrentTournamentRequest(const int &index) override;
    /*
     * UI request data to populate scoreboard
     */
    void handleRequestForSingleThrowScoreData() override;
    void handleRequestForMultiThrowScoreData() override;
    /*
     * Create tournament
     *
     *  Data array allocates memmory locations in the following order:
     *   - [0] = Gamemode
     *   - [1] = Keypoint
     *   - [2] = KeyCode (win condition)
     *   - [3] = TableViewHint
     *   - [4] = InputMode
     *   - [5] = Number of throws
     */
    void handleFTPDetails(const QString &title,
                                const QVector<int> &data,
                                const QVector<int> &playerIndexes) override;
    /*
     * Delete tournament
     */
    void handleDeleteTournamentsRequest(const QVariantList &indexes) override;
    /*
     * UI requests to create/delete player from datacontext
     */
    void handleCreatePlayer(const QString &playerName, const QString &email) override;
    void handleDeletePlayer(const int &index) override;
    void handleDeletePlayersRequest(const QVariantList &args) override;
    /*
     * UI requests playerdetails from datacontext
     */
    void requestPlayerDetails() override;
    void handleSendGameModesRequest() const override;
    /*
     *  - Start/stop tournament
     *  - Reset and restart tournament
     */
    void handleRequestStart() override;
    void handleRequestStop() override;
    void handleRestartTournament() override;
    /*
     * Handle UI user input
     *  - Users enters points to be stored in datacontext
     *  - In return, datacontext, in collaboration with gamecontroller, send current score to UI
     */
    void handleUserInput(const int &point, const int &pressedModfier) override;
    void handleUndoRequest() override;
    void handleRedoRequest() override;
    void handleControllerStateRequest() override;
    /*
     * Handle request for tournament meta information
     */
    void handleTournamentMetaRequest() override;
    /*
     * Handle request for tournament persist
     */
    void handlePersistTournamentRequest() override;

signals:
    void assembleFTPController(const QVector<QUuid> &idAndWinner,
                               const QVector<int> &values,
                               const QVector<QUuid> &userIds,
                               const QVector<QString> &playerNames,
                               AbstractApplicationInterface* applicationsInteface,
                               AbstractModelsContextInterface* modelsContextInterface);
private slots:
    void assembleAndConfigureControllerBuilder(const QVector<QUuid>& idAndWinner,
                                    const QVector<int> &values,
                                    const QVector<QUuid> &userIds,
                                    const QVector<QString> &playerNames);
    void setGameController(AbstractGameController* controller);
private:
    // Register and connect interfaces related..
    void registerTypes();
    void connectModelInterfaces();
    // Clear controller..
    void clearGameController();

    // Threads related..
    bool usingThreads() const;
    void setUsingThreads(bool usingThreads);
    void startModelsContextInterfaceThread();
    void stopModelsInterfaceThread();
    // Builders related..
    AbstractGameController *gameController() const;
    AbstractControllerBuilder* controllerBuilder() const;
    // Application state member variables
    bool _usingThreads;
    QThread* _modelsContextInterfaceThread = new QThread();
    QThread *_gameControllerThread = new QThread();
    AbstractControllerBuilder *_controllerBuilder;
    AbstractModelsContextInterface* _modelsContext;
    AbstractGameController *_gameController = nullptr;
};

#endif // PROJECTDARTINTERFACE_H
