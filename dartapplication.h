#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>
#include <qthreadpool.h>
#include <iostream>

#include "itournamentbuilder.h"
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
     * Get/set GameControllerBuilder
     */
    AbstractControllerBuilder* controllerBuilder();
    DartApplication *setControllerBuilder(ControllerBuilderInterface *builder);

public slots:
    /*
     * Get/set modelcontext interface
     */
    virtual AbstractModelsContext *modelsContextInterface() const override;
    virtual DartApplication* setModelsContextInterface(AbstractModelsContext *modelsInterface) override;
    // Get tournaments
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
    void handleFTPDetails(const QByteArray &json) override;
    /*
     * Delete tournament
     */
    void handleDeleteTournamentsRequest(const QByteArray &json) override;
    /*
     * UI requests to create/delete player from datacontext
     */
    void handleCreatePlayer(const QByteArray &json) override;
    void handleDeletePlayer(const QByteArray &json) override;
    void handleDeletePlayersRequest(const QByteArray &json) override;
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
    void handleUserInput(const QByteArray& json) override;
    void handleUndoRequest() override;
    void handleRedoRequest() override;
    void handleControllerStateRequest() override;
    /*
     * Handle request for tournament meta information
     */
    void handleTournamentMetaRequest() override;

signals:
    void assembleFTPController(const QByteArray& json,
                               AbstractApplicationInterface* applicationsInteface,
                               AbstractModelsContext* modelsContextInterface);
private slots:
    void assembleAndConfigureControllerBuilder(const QByteArray &json);
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
    AbstractModelsContext* _modelsContext;
    AbstractGameController *_gameController = nullptr;
};

#endif // PROJECTDARTINTERFACE_H
