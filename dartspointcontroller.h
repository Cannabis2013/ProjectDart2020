#ifndef DARTSPOINTSINGLEATTEMPT_H
#define DARTSPOINTSINGLEATTEMPT_H

// Proprietary QT classes
#include <quuid.h>
// Custom classes
#include "abstractdartspointcontroller.h"
#include "idartslogisticsservice.h"
#include "IPointCalculatorService.h"
#include "ipointvalidator.h"
#include "idartspointindexservice.h"
#include "iplayerpointservice.h"
#include "idartscontrollerpoint.h"
#include "dartspointturnvalues.h"
#include "idartspointcontrollerindexes.h"
#include "idartscontrollermodelsservice.h"
#include "idartscontrollerpointbuilder.h"
#include "idartscontrollerindexesbuilder.h"
#include "idartscontrollerplayer.h"
#include "idartsplayermodelbuilderservice.h"
#include "ibuilddartspointturnvalues.h"
#include "icombinejsonbytearrayservice.h"
/*
 * Services
 */
#include "iaddtotalscoretodartsinputs.h"
// Json services
#include "idartscontrollerjsonservice.h"
#include "igetordereddartspointsbyjson.h"
#include "idartsinputstojson.h"
#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

namespace DartsPointControllerContext {

    class DartsPointController : public AbstractDartsPointController
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
        // Commonly used models typedefinitions
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
        typedef IDartsControllerPlayer<QUuid,QString> ControllerPlayer;
        typedef IDartsControllerpointBuilder<IControllerPoint,QByteArray,QUuid,QString> ControllerPointBuilder;
        // Build darts indexes by json service
        typedef IDartsPointIndexService<IDartsPointControllerIndexes> DartsIndexService;
        typedef IDartsControllerIndexesBuilder<IDartsPointControllerIndexes,
                                                    DartsIndexService,
                                                    QByteArray> IIndexesBuilderService;
        typedef IDartscontrollerJsonService<IControllerPoint,
                                       IDartsPointControllerIndexes,
                                       QByteArray,QUuid> DartsJsonService;
        typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerPointService;
        typedef IDartsLogisticsService<QString> LogisticService;
        typedef IBuildDartsPointTurnValues TurnValueBuilderService;
        typedef IDartsControllerModelsService<IDartsControllerPoint<QUuid,QString,QByteArray>,QString,QUuid> ControllerModelsService;
        typedef IPointCalculatorService<IControllerPoint> ScoreCalculatorService;
        typedef IDartsPlayerModelBuilderService<ControllerPlayer,QByteArray> PlayerModelBuilder;
        typedef IDartsInputsToJson<IControllerPoint,QByteArray> DartsInputsToJsonService;
    public slots:
        /*
         * Initialize controller with:
         *  - index values
         *  - score values,
         *  - player values
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
        void handleOrderedDartsPoint(const QByteArray &json) override;
        /*
         * Models context succesfully persisted point
         */
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
    protected:
        /*
         * Protected constructor
         */
        DartsPointController(const QUuid &tournament, const int &displayHint);
        // Services
        // Builder Services
        TurnValueBuilderService* _dartsTurnValuesBuilderService;
        ControllerPointBuilder* _pointModelBuilderService;
        PlayerModelBuilder* _playerModelBuilderService;
        IIndexesBuilderService* _dartsIndexesBuilderService;
        ControllerModelsService* _controllerModelsService;
        /*
         * Model manipulating services
         */
        IAddTotalScoreToDartsInputs *_addTotalScoresServices;
        // Json
        DartsInputsToJsonService * _dartsPointsToJson;
        DartsJsonService* _dartsJsonService;
        IGetOrderedDartsPointByJson *_getOrderedDartsPointsByJson;
        ICombineJsonByteArray *_combineDartsIndexesAndDartsPoint;

        // Calculate score
        ScoreCalculatorService* _calculateScoreByPointInput = nullptr;
        // Generate throwsuggestions
        LogisticService *_pointLogisticInterface = nullptr;
        // Validator service
        IPointValidator* _inputEvaluator = nullptr;
        // Index service
        DartsIndexService* _indexController = nullptr;
        // Userscore service
        PlayerPointService* _playerPointsService = nullptr;
    private:
        void updatePlayerPointModel(const IControllerPoint *pointModel);
        QByteArray createJson(const IDartsPointControllerIndexes* indexes, const IControllerPoint *pointModel);
        void setStateIfNoWinnerDetermined();
        void processDomain(const int& domain,
                           const int& point, const int &score,
                           const int& modKeyCode);
        /*
         * Notify UI about controller state, current round index, undo/redo possibility and current user
         */
        void sendCurrentTurnValues();
        QString currentUserName()  ;
        QUuid currentPlayerId();
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
        int _displayHint;
        QUuid _tournament = QUuid();
        int _currentStatus = ControllerState::NotInitialized;
    };
}
#endif // POINTFTPCONTROLLER_H
