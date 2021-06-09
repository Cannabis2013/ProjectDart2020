#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>
#include <iostream>

#include "itournamentbuilder.h"
#include "abstractdartscontrollerbuilder.h"
#include "abstractmodelsservicebuilder.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "qdebug.h"
#include "abstractroutebygamemode.h"
#include "abstractdartsscorecontroller.h"
#include "abstractdartspointcontroller.h"
#include "abstractroutebyinputhint.h"
#include "abstractroutebydisplayhint.h"
#include "iconnectroutetodartsbuilder.h"
#include "iconnectdartspointcontroller.h"
#include "iconnectdartsscorecontroller.h"
#include "iconnectmodelsinterface.h"
#include "iconnectroutebyinputhint.h"
#include "iconnectroutebydisplayhint.h"

using namespace std;

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication : public AbstractApplicationInterface
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    typedef IBinaryService<AbstractModelsService*,AbstractRouteByGameMode*,void> ConnectRouteByGameMode;
    /*
     * Create and setup instance
     */
    static DartApplication* createInstance();
    DartApplication *setup();
    DartApplication *useThreads();
    void registerTypes();
    /*
     * Get/set GameControllerBuilder
     */
    AbstractDartsControllerBuilder* controllerBuilder();
    DartApplication *setDartsPointBuilderService(ControllerBuilderInterface *builder);

    DartApplication *setModelsServiceBuilder(
            AbstractModelsServiceBuilder<AbstractModelsService> *modelsServiceBuilder);
    // Set services methods
    DartApplication *setConnectModelsServiceInterface(IConnectModelsInterface *connectModelsServiceInterface);
    DartApplication *setDetermineTournamentGameMode(AbstractRouteByGameMode *newDetermineTournamentGameMode);
    DartApplication *setConnectRouteByGameMode(ConnectRouteByGameMode *newConnectTournamentGameModeService);
    DartApplication *setDartsScoreControllerBuilder(AbstractDartsControllerBuilder *service);
    DartApplication *setDartsScoreBuilder(AbstractDartsControllerBuilder *service);
    DartApplication *setConnectToDartsPountBuilder(IConnectRouteToDartsBuilder *newConnectToDartsPountBuilder);
    DartApplication *setConnectToDartsScoreBuilder(IConnectRouteToDartsBuilder *newConnectToDartsScoreBuilder);
    DartApplication *setConnectDartsPointController(IConnectDartsPointController *newConnectDartsPointController);
    DartApplication *setConnectDartsScoreController(IConnectDartsScoreController *newConnectDartsScoreController);
    DartApplication *setRouteByInputHint(AbstractRouteByInputHint *newRouteByInputHint);
    DartApplication *setRouteByDisplayHint(AbstractRouteByDisplayHint *newRouteByDisplayHint);
    DartApplication *setConnectRouteByDisplayHint(IConnectRouteByDisplayHint *newConnectRouteByDisplayHint);
    DartApplication *setConnectRouteByInputHint(IConnectRouteByInputHint *newConnectRouteByInputHint);

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
    void handleRequestForDartsSingleAttemptPoints() override;
    void handleRequestForMultiAttemptScores() override;
    /*
     * Create tournament
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
    void handleDartsSingleAttemptInput(const QByteArray& json) override;
    void handleDartsMultiAttemptInput(const QByteArray& json) override;
    void handleUndoRequest() override;
    void handleRedoRequest() override;
    void handleControllerStateRequest() override;
    /*
     * Handle request for tournament meta information
     */
    void assembleDartsTournamentValues() override;
    /*
     * Set game controller methods
     */
    void setDartsPointSingleAttempt(AbstractDartsController *controller) override;
    void setDartsScoreMultiAttempt(AbstractDartsController *controller) override;
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
    AbstractDartsController* _dartsController;
    AbstractModelsService* _modelsService;
    AbstractGameController *_gameController = nullptr;
    /*
     * Builders
     */
    AbstractDartsControllerBuilder *_dartsPointBuilder;
    AbstractDartsControllerBuilder *_dartsScoreBuilder;

    AbstractModelsServiceBuilder<AbstractModelsService>* _modelsServiceBuilder;
    /*
     * Route services
     */
    AbstractRouteByGameMode* _routeByGameMode;
    AbstractRouteByInputHint* _routeByInputHint;
    AbstractRouteByDisplayHint* _routeByDisplayHint;

    /*
     * Connect route services
     */
    IConnectRouteToDartsBuilder *_connectDartsPointBuilder;
    IConnectRouteToDartsBuilder *_connectDartsScoreBuilder;
    /*
     * Connect darts controller services
     */
    IConnectRouteByInputHint* _connectRouteByInputHint;
    IConnectRouteByDisplayHint* _connectRouteByDisplayHint;
    IConnectDartsPointController* _connectDartsPointController;
    IConnectDartsScoreController* _connectDartsScoreController;
    ConnectRouteByGameMode* _connectRouteByGameMode;
    IConnectModelsInterface* _connectModelsServiceInterface;
};

#endif // PROJECTDARTINTERFACE_H
