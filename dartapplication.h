#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>
#include <qthreadpool.h>
#include <iostream>

#include "itournamentbuilder.h"
#include "abstractdartscontrollerbuilder.h"
#include "abstractmodelsservicebuilder.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"

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
    AbstractDartsControllerBuilder* controllerBuilder();
    DartApplication *setControllerBuilder(ControllerBuilderInterface *builder);

    DartApplication *setModelsServiceBuilder(
            AbstractModelsServiceBuilder<AbstractModelsService> *modelsServiceBuilder);

    DartApplication *setConnectModelsServiceInterface(IBinaryService<AbstractApplicationInterface *, AbstractModelsService *, void> *connectModelsServiceInterface);

    DartApplication* setConnectControllerBuilder(ITernaryService<AbstractApplicationInterface *, AbstractDartsControllerBuilder *, AbstractModelsService *, void> *connectControllerBuilder);

public slots:
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
    void handleRequestForDartsSingleAttemptPoints() override;
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
    void handleSingleAttemptPlayerPointInput(const QByteArray& json) override;
    void handleUndoRequest() override;
    void handleRedoRequest() override;
    void handleControllerStateRequest() override;
    /*
     * Handle request for tournament meta information
     */
    void assembleDartsTournamentValues() override;

    void assembleAndConfigureControllerBuilder(const QByteArray &json) override;
    void setGameController(AbstractGameController* controller) override;
private:
    DartApplication();
    // Clear controller..
    void clearGameController();

    // Threads related..
    bool usingThreads() const;
    void setUsingThreads(bool usingThreads);
    void startModelsContextInterfaceThread();
    void stopModelsInterfaceThread();
    // Builders related..
    AbstractGameController *gameController() const;
    AbstractDartsControllerBuilder* controllerBuilder() const;
    // Application state member variables
    bool _usingThreads;
    QThread* _modelsContextInterfaceThread = new QThread();
    QThread *_gameControllerThread = new QThread();
    AbstractDartsControllerBuilder *_controllerBuilder;
    AbstractModelsService* _modelsContext;
    AbstractGameController *_gameController = nullptr;
    AbstractModelsServiceBuilder<AbstractModelsService>* _modelsServiceBuilder;
    /*
     * Connect-services
     */
    IBinaryService<AbstractApplicationInterface*,
                   AbstractModelsService*,
                   void>* _connectModelsServiceInterface;
    ITernaryService<AbstractApplicationInterface*,
                    AbstractDartsControllerBuilder*,
                    AbstractModelsService*,void>* _connectControllerBuilder;
};

#endif // PROJECTDARTINTERFACE_H
