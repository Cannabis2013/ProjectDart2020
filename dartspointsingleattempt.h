#ifndef POINTFTPCONTROLLER_H
#define POINTFTPCONTROLLER_H

// Proprietary QT classes
#include <quuid.h>
// Custom classes
#include "abstractdartspointcontroller.h"
#include "idartslogisticsservice.h"
#include "IPointCalculatorService.h"
#include "ipointvalidator.h"
#include "idartssingleattemptindexservice.h"
#include "iplayerscoreservice.h"
// Json services
#include "IDartsSingleAttemptPointJsonService.h"
#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

using namespace std;

class DartsPointSingleAttempt : public AbstractDartsPointController
{
    Q_OBJECT
public:
    // Public types
    enum InputDomains {
        PointDomain = 0x01,
        CriticalDomain = 0x02,
        OutsideDomain = 0x03,
        TargetDomain = 0x4,
        OutOfRange = 0x5
    };
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    enum ControllerState {
        GameBusy = 0x11, // Game is idle but in progress
        Stopped = 0x12, // Game is stopped and no longer accepts input
        AwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
        WinnerDeclared = 0x15,
        NotInitialized = 0x16, // Controller is not initialized with tournament and, if necessary, appropriate indexes
        Initialized = 0x17,
        UndoState = 0x1F,
        RedoState = 0x20,
        AddScoreState = 0x21,
        UpdateContextState = 0x22,
        resetState = 0x29,
        idle = 0xA
    };
    enum ControllerResponse{
        IsProcessingUserInput = 0x46
    };
    // Create instance of LocalFTPController
    static DartsPointSingleAttempt* createInstance(const QUuid &tournament);
    // Set service methods
    DartsPointSingleAttempt *setScoreCalculator(IPointCalculatorService* scoreCalculator);
    DartsPointSingleAttempt *setInputValidator(IPointValidator* scoreEvaluator);
    DartsPointSingleAttempt *setIndexController(IDartsSingleAttemptIndexService *indexController);
    DartsPointSingleAttempt *setInputController(IPlayerScoreService *scoreController);
    /*
     * Point suggestion section
     */
    IDartsLogisticsService<QString> *pointLogisticInterface() const;
    DartsPointSingleAttempt* setLogisticInterface(IDartsLogisticsService<QString> *pointLogisticInterface);
    DartsPointSingleAttempt* setDartsJsonModelsService(IDartsSingleAttemptPointJsonService *dartsJsonModelsService);

public slots:
    /*
     * Recieve darts index values, score values,
     *  and player values from modelscontext
     */
    void beginInitialize() override;
    virtual void initializeControllerIndexes(const QByteArray& json) override;
    void initializeControllerPlayerDetails(const QByteArray &json) override;
    void initializeControllerDartsPoints(const QByteArray &json) override;
    void initializeControllerWinnerIdAndName(const QByteArray &json) override;
    /*
     * Start/stop/undo/redo
     */
    void start() override;
    void stop() override;
    QUuid undoTurn() override;
    QUuid redoTurn() override;
    /*
     * Controller starts initializing
     *  - Request tournament id from index provided by calling context
     *  - Request basic values
     *  - Request controller indexes
     *  - Request current playerscores
     */
    /*
     * Handle status request from UI
     */
    void handleRequestFromUI() override;
    /*
     * Handle and Evaluate input from user
     */
    void handleAndProcessUserInput(const QByteArray &json) override;
    /*
     * Send current tournament id to external context
     */
    void handleRequestForCurrentTournamentMetaData() override;
    void handleRequestDartsPoints() override;

    void handlePointAddedToDataContext(const QByteArray& json) override;
    /*
     * Reinitialize controller
     *  - Set controller back to its original state
     */
    void handleResetTournament() override;
    // Get current status
    int currentStatus() const;
    /*
     * Undo/redo success
     */
    void undoSuccess(const QByteArray &json) override;
    void redoSuccess(const QByteArray &json) override;

private:
    /*
     * Private constructor
     */
    DartsPointSingleAttempt(const QUuid &tournament)
    {
        _tournament = tournament;
    }
    /*
     * Check if controller is busy doing something else
     */
    bool isBusy();
    void processDomain(const int& domain,
                       const int& point, const int &score,
                       const int& modKeyCode);
    /*
     * Notify UI about controller state, current round index, undo/redo possibility and current user
     */
    void sendCurrentTurnValues();
    QString currentActiveUser()  ;
    QUuid currentActivePlayerId();
    QUuid tournament();
    int status();
    void setCurrentStatus(int currentStatus);
    int lastPlayerIndex();
    /*
     * Update datacontext
     */
    void addPoint(const int &point, const int &score,
                  const int &keyCode);
    /*
     * Index manipulating methods
     */
    void nextTurn();
    void declareWinner();
    // Member variables
    QUuid _tournament = QUuid();
    int _currentStatus = ControllerState::NotInitialized;
    //Services
    // Json
    IDartsSingleAttemptPointJsonService* _dartsJsonModelsService;
    // Calculate score
    IPointCalculatorService* _scoreCalculator = nullptr;
    // Generate throwsuggestions
    IDartsLogisticsService<QString> *_pointLogisticInterface = nullptr;
    // Validator service
    IPointValidator* _scoreEvaluator = nullptr;
    // Index service
    IDartsSingleAttemptIndexService* _indexController = nullptr;
    // Userscore service
    IPlayerScoreService* _scoreController = nullptr;
};

#endif // POINTFTPCONTROLLER_H
