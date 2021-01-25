#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H
// Proprietary QT classes
#include <QVariantList>
#include <quuid.h>
#include <qlist.h>
#include <qthread.h>
// Custom classes
#include "abstractgamecontroller.h"
#include "ipointlogisticinterface.h"
#include "scoreCalculatorInterface.h"
#include "inputvalidatorinterface.h"
#include "indexcontrollerinterface.h"
#include "userscorescontrollerinterface.h"


#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

#include <iostream>


typedef UserScoresControllerInterface<QUuid, QString,QVector<int>,QVector<QString>> UserScoreController;

using namespace std;

class LocalFTPController : public AbstractGameController
{
    Q_OBJECT
public:
    // Public types
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
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
        isStopped = 0x3A,
        isIdle = 0x3B,
        ScoreTransmit = 0x27,
        ScoresTransmit = 0xA,
        ScoreRemove = 0x28,
        initializedAndAwaitsInput = 0x2D,
        initializedAndReady = 0x45,
        WinnerFound = 0x3E,
        isProcessingUserInput,
        tournamentIsReset = 0x29
    };
    // Create instance of LocalFTPController
    static LocalFTPController* createInstance(const QUuid &tournament);
    /*
     * Point suggestion section
     */
    IPointLogisticInterface<QString> *pointLogisticInterface() const;
    LocalFTPController *setPointLogisticInterface(IPointLogisticInterface<QString> *pointLogisticInterface);
    /*
     * Handle wake up request
     *  - Set status to 'InitializedAndReady'
     *  - Transmit 'ready' response
     */
    void handleWakeUpRequest() override;
    /*
     * Start/stop game progress
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
    void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) override;
    /*
     * Send current tournament id to external context
     */
    void handleRequestForCurrentTournamentMetaData() override;
    /*
     * Handle request for playerscores
     *
     * The following methods is called dependently on input hint
     */
    void handleRequestForSingleThrowPlayerScores() override;
    void handleRequestForMultiThrowPlayerScores() override;

    void handleScoreAddedToDataContext(const QUuid &playerID,
                                              const int &point,
                                              const int &score) override;
    void handleScoreHintUpdated(const QUuid &playerID,
                                       const int &point,
                                       const int &score) override;
    /*
     * Reinitialize controller
     *  - Set controller back to its original state
     */
    void handleResetTournament() override;
    void handleTournamentResetSuccess() override;
    /*
     * Handle persist controller state
     */
    void handleRequestPersistCurrentState() override;
    /*
     * Handle persist modelstate done
     */
    void handlePersistModelStateDone() override;
    /*
     * Get/set score calculator service
     */
    ScoreCalculatorInterface* scoreCalculator() const;
    LocalFTPController *setScoreCalculator(ScoreCalculatorInterface *service);
    /*
     * Get/set evaluator service
     */
    InputValidatorInterface *scoreEvaluator() const;
    LocalFTPController *setInputValidator(InputValidatorInterface *scoreEvaluator);

    IndexControllerInterface *indexController() const;
    LocalFTPController *setIndexController(IndexControllerInterface *indexController);

    UserScoreController* scoreController() const;
    LocalFTPController *setScoreController(UserScoreController *scoreController);
    // Get current status
    int currentStatus() const;
private:
    /*
     * Private constructor
     */
    LocalFTPController(const QUuid &tournament)
    {
        _tournament = tournament;
    }
    /*
     * Notify UI about controller state, current round index, undo/redo possibility and current user
     */
    void sendCurrentTurnValues();
    QString currentActiveUser()  ;
    QUuid currentActivePlayerID();
    QUuid tournament();
    int status();
    void setCurrentStatus(int currentStatus);
    int lastPlayerIndex();
    /*
     * Update datacontext
     */
    void addPoint(const int &point, const int &score);
    /*
     * Set controller state according to datacontext
     */
    /*
     * Index manipulating methods
     */
    void nextTurn();
    void declareWinner();
    // Current tournament id
    QUuid _tournament = QUuid();
    /*
     * Status member variable
     */
    int _currentStatus = ControllerState::NotInitialized;
    //Services
    // Calculate score
    ScoreCalculatorInterface* _scoreCalculatorService;
    // Generate throwsuggestions
    IPointLogisticInterface<QString> *_pointLogisticInterface;
    // Validator service
    InputValidatorInterface* _scoreEvaluator;
    // Index service
    IndexControllerInterface* _indexController;
    // Userscore service
    UserScoreController* _scoreController;
};



#endif // FIVEHUNDREDANDONEGAME_H
