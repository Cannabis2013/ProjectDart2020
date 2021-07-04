#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <qthread.h>
/*
 * Include services
 */
#include "connectdartspointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "connectdefaultmodelscontextinterface.h"
#include "localmodelsservicewithjsondb.h"
#include "dartspointcontrollerbuilder.h"
#include "dartsscorebuilderservice.h"
#include "BuildDartsControllerEntity.h"
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
    void registerTypes();
    DartApplication *createDartsBuilders();
    DartApplication *connectServices();
    DartApplication *useThreads();
    /*
     * Get/set GameControllerBuilder
     */
    AbstractDartsControllerBuilder* controllerBuilder();
    DartApplication *setDartsPointBuilderService(ControllerBuilderInterface *builder);
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
    /*
     * Create tournament
     */
    void handleDartsDetails(const QByteArray &json) override;
    void handleSendGameModesRequest() const override;
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
    AbstractModelsService* _modelsService = new LocalModelsServiceWithJsonDb;
    AbstractGameController *_gameController = nullptr;
    /*
     * Builders
     */
    AbstractDartsControllerBuilder *_dartsPointBuilder;
    AbstractDartsControllerBuilder *_dartsScoreBuilder;
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
