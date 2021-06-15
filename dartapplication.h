#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <qthread.h>
/*
 * Include services
 */
#include "connectdartspointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "defaultmodelsservicebuilder.h"
#include "dartspointbuilderservice.h"
#include "dartsscorebuilderservice.h"
#include "BuildDartsControllerEntity.h"
#include "buildsingleattemptpointcontroller.h"
#include "buildmultiattemptscorecontroller.h"
#include "routebytournamentgamemode.h"
#include "connectroutebygamemode.h"
#include "connectdartspointbuilder.h"
#include "ConnectDartsScoreBuilder.h"
#include "connectdartsscorecontroller.h"
#include "connectdartspointcontroller.h"
#include "routedartsbyinputhint.h"
#include "routebydisplayhint.h"
#include "connectroutebyinputhint.h"
#include "connectroutebydisplayhint.h"

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication : public AbstractApplicationInterface
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    typedef IBinaryService<AbstractModelsService*,AbstractRouteByGameMode*,void> IConnectRouteByGameMode;
    /*
     * Create and setup instance
     */
    static DartApplication* createInstance();
    static DartApplication* createAndSetupInstance();
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
    void handleDartsPointInput(const QByteArray& json) override;
    void handleDartsScoreInput(const QByteArray& json) override;
    void handleDartsUndoRequest() override;
    void handleDartsRedoRequest() override;
    void handleControllerStateRequest() override;
    /*
     * Handle request for tournament meta information
     */
    void assembleDartsTournamentValues() override;
    /*
     * Set game controller methods
     */
    void setDartsPointController(AbstractDartsController *controller) override;
    void setDartsScoreController(AbstractDartsController *controller) override;
private:
    /*
     * Private constructor
     */
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
    AbstractModelsServiceBuilder<AbstractModelsService>* _modelsServiceBuilder = DefaultModelsServiceBuilder::createInstance();
    /*
     * Route services
     */
    AbstractRouteByGameMode* _routeTournamentByGameMode = new RouteByTournamentGameMode;
    AbstractRouteByInputHint* _routeDartsControllerByInputHint = new RouteDartsByInputHint;
    AbstractRouteDartsByDisplayHint* _routeDartsControllerByDisplayHint = new RouteByDisplayHint;

    /*
     * Connect route services
     */
    IConnectRouteByGameMode* _connectRouteByGameMode = new ConnectRouteByGameMode();
    IConnectRouteByInputHint* _connectRouteByInputHint = new ConnectRouteByInputHint;;
    IConnectRouteByDisplayHint* _connectRouteByDisplayHint = new ConnectRouteByDisplayHint;
    /*
     * Connect darts controller services
     */
    IConnectRouteToDartsBuilder *_connectDartsPointBuilder = new ConnectDartsPointBuilder;
    IConnectRouteToDartsBuilder *_connectDartsScoreBuilder = new ConnectDartsScoreBuilder;
    IConnectDartsPointController* _connectDartsPointController = new ConnectDartsPointController;
    IConnectDartsScoreController* _connectDartsScoreController = new ConnectDartsScoreController;
    IConnectModelsInterface* _connectModelsServiceInterface = new ConnectDefaultModelsContextInterface;
};

#endif // PROJECTDARTINTERFACE_H
