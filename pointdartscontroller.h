#ifndef POINTFTPCONTROLLER_H
#define POINTFTPCONTROLLER_H

// Proprietary QT classes
#include <quuid.h>
#include <qvariant.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QJsonDocument>
// Custom classes
#include "abstractgamecontroller.h"
#include "ftplogisticcontrollerinterface.h"
#include "scoreCalculatorInterface.h"
#include "ipointvalidator.h"
#include "indexcontrollerinterface.h"
#include "iscorecontroller.h"

#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

#include <iostream>
#include "AbstractDartsController.h"


typedef IScoreController<QUuid, QString,QVector<int>,QVector<QString>> ScoreController;

using namespace std;

class PointDartsController : public AbstractDartsController
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
    static PointDartsController* createInstance(const QUuid &tournament);
    /*
     * Get/set score calculator service
     */
    ScoreCalculatorInterface* scoreCalculator() const;
    PointDartsController *setScoreCalculator(ScoreCalculatorInterface *service);
    /*
     * Get/set evaluator service
     */
    IPointValidator *scoreEvaluator() const;
    PointDartsController *setInputValidator(IPointValidator
                                          *scoreEvaluator);

    IndexControllerInterface *indexController() const;
    PointDartsController *setIndexController(IndexControllerInterface *indexController);

    ScoreController* scoreController() const;
    PointDartsController *setScoreController(ScoreController *scoreController);
    /*
     * Point suggestion section
     */
    FTPLogisticControllerInterface<QString> *pointLogisticInterface() const;
    PointDartsController *setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface);
public slots:
    /*
     * Handle wake up request
     *  - Set status to 'InitializedAndReady'
     *  - Transmit 'ready' response
     */
    void beginInitialize() override;
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
    /*
     * Handle request for playerscores
     *
     * The following methods is called dependently on input hint
     */
    void assembleSingleAttemptFtpScores() override;
    void handleRequestFtpPlayerScores() override;

    void handleScoreAddedToDataContext(const QByteArray& json) override;
    void handleScoreHintUpdated(const QByteArray& json) override;
    /*
     * Reinitialize controller
     *  - Set controller back to its original state
     */
    void handleResetTournament() override;
    /*
     * Handle persist controller state
     */
    void handleRequestPersistCurrentState() override;
    // Get current status
    int currentStatus() const;
    /*
     * Recieve ftp index values, score values, and player values from modelscontext
     */
    virtual void initializeController(const QByteArray& json) override;
private:
    /*
     * Private constructor
     */
    PointDartsController(const QUuid &tournament)
    {
        _tournament = tournament;
    }
    /*
     * Check if controller is busy doing something else
     */
    bool isBusy();
    void processDomain(const int& domain, const int &score,
                       const int& point,
                       const int& modKeyCode, const int &currentScore,
                       const int& accumulatedScore);
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
    void addPoint(const int &point,
                  const int &score,
                  const int &accumulatedScore,
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
    // Calculate score
    ScoreCalculatorInterface* _scoreCalculatorService = nullptr;
    // Generate throwsuggestions
    FTPLogisticControllerInterface<QString> *_pointLogisticInterface = nullptr;
    // Validator service
    IPointValidator* _scoreEvaluator = nullptr;
    // Index service
    IndexControllerInterface* _indexController = nullptr;
    // Userscore service
    ScoreController* _scoreController = nullptr;
};

#endif // POINTFTPCONTROLLER_H
