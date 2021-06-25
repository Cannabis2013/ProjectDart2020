#ifndef DARTSPOINTSINGLEATTEMPT_H
#define DARTSPOINTSINGLEATTEMPT_H

// Proprietary QT classes
#include <quuid.h>
// Custom classes
#include "abstractdartspointcontroller.h"
// Models
#include "idartscontrollerpoint.h"
#include "dartspointturnvalues.h"
#include "idartspointcontrollerindexes.h"
#include "idartscontrollerplayer.h"
/*
 * Services
 */
#include "iaddtotalscoretodartsinputsjson.h"
#include "iaddplayernamestojsonentity.h"
#include "idartsplayermodelbuilderservice.h"
#include "ibuilddartspointturnvalues.h"
#include "ibytearrayjsonmerger.h"
#include "idartslogisticsservice.h"
#include "IPointCalculatorService.h"
#include "ipointvalidator.h"
#include "iplayerpointservice.h"
#include "idartscontrollermodelsservice.h"
#include "idartscontrollerindexesbuilder.h"
#include "idartscontrollerpointbuilder.h"
#include "idartspointindexservice.h"
#include "iaddtotalscoretodartspoint.h"
#include "idartsmetadata.h"
// Json services
#include "iqtjsonbuilder.h"
#include "iqtjsonextractor.h"
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
            WinnerDeclared = 0x15
        };
        // Commonly used models typedefinitions
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
        typedef IDartsControllerPlayer<QUuid,QString,QByteArray> ControllerPlayer;
        typedef IDartsControllerpointBuilder<IControllerPoint,QByteArray,QUuid,QString> ControllerPointBuilder;
        // Build darts indexes by json service
        typedef IDartsPointControllerIndexes<QByteArray> DartsIndexes;
        typedef IDartsPointIndexService<DartsIndexes> DartsIndexService;
        typedef IDartsControllerIndexesBuilder<DartsIndexes,DartsIndexService,QByteArray> IIndexesBuilderService;
        typedef IDartscontrollerJsonService<IControllerPoint,DartsIndexes,QByteArray,QUuid> DartsJsonService;
        typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerPointService;
        typedef IDartsLogisticsService<QString> LogisticService;
        typedef IBuildDartsPointTurnValues TurnValueBuilderService;
        typedef IDartsControllerModelsService<IDartsControllerPoint<QUuid,QString,QByteArray>,QString,QUuid> ControllerModelsService;
        typedef IPointCalculatorService<IControllerPoint> ScoreCalculatorService;
        typedef IDartsPlayerModelBuilderService<ControllerPlayer,QString,QUuid,QByteArray> PlayerModelBuilder;
        typedef IDartsInputsToJson<IControllerPoint,QByteArray> DartsInputsToJsonService;
        typedef IAddTotalScoreToDartsInputsJson<QByteArray> AddTotalScoresToJsonEntities;
        typedef IAddPlayerNamesToJsonEntity<QByteArray> AddPlayerNamesToJsonEntities;
    public slots:
        /*
         * Initialize phase I (controller instantiation phase):
         *  - index values
         *  - player details
         *  - score values
         *  - winner details
         */
        void beginInitialize() override;
        virtual void initializeControllerIndexes(const QByteArray& json) override;
        void initializeControllerPlayerDetails(const QByteArray &json) override;
        void initializeControllerDartsPoints(const QByteArray &json) override;
        void initializeControllerWinnerIdAndName(const QByteArray &json) override;
        /*
         * Initialize phase II (UI request tournament meta data):
         *  - Handle request for basic tournament metadata like:
         *      * Title
         *      * Keypoint
         *      * attempts
         *      * players details
         *      * etc.
         *  - Handle request for dartspoints ordered by indexes
         */
        void handleRequestForCurrentTournamentMetaData() override;
        void handleRequestOrderedDartsPoints() override;
        void handleOrderedDartsPoint(const QByteArray &json) override;
        /*
         * Start/stop/undo/redo
         */
        void start() override;
        void stop() override;
        QUuid undoTurn() override;
        QUuid redoTurn() override;
        /*
         * Handle status request from UI
         */
        void handleRequestFromUI() override;
        /*
         * Handle and Evaluate input from user
         */
        void handleAndProcessUserInput(const QByteArray &json) override;
        /*
         * Models context succesfully persisted point
         */
        void handlePointAddedToDataContext(const QByteArray& json) override;
        /*
         * Reinitialize controller
         *  - Set controller back to its original state
         */
        void handleResetTournament() override;
        /*
         * Undo/redo success
         */
        void undoSuccess(const QByteArray &json) override;
        void redoSuccess(const QByteArray &json) override;
    protected:
        /*
         * Protected constructor
         */
        // Services
        // Builder Services
        TurnValueBuilderService* _turnValuesBuilder;
        ControllerPointBuilder* _pointModelBuilder;
        PlayerModelBuilder* _playerModelBuilder;
        IIndexesBuilderService* _dartsIndexesBuilder;
        ControllerModelsService* _controllerModels;
        // Meta information
        IDartsMetaData *_metaData;
        // Model manipulating services
        IAddTotalScoreToDartsPoint *_addTotalScoreToPointModel;
        // Json
        IQtJsonBuilder *_jsonBuilder;
        IQtJsonExtractor *_jsonExtractor;
        IGetOrderedDartsPointByJson *_getOrderedDartsPointsByJson;
        AddTotalScoresToJsonEntities *_addTotalScoresToDartsModelsJson;
        DartsInputsToJsonService * _dartsPointsToJson;
        IByteArrayJsonMerger *_jsonMerger;
        AddPlayerNamesToJsonEntities *_addPlayerNamesToDartsModelsJson;
        // Calculate score
        ScoreCalculatorService* _calculateScoreByPointInput = nullptr;
        // Generate throwsuggestions
        LogisticService *_stringSuggestionService = nullptr;
        // Validator service
        IPointValidator* _inputEvaluator = nullptr;
        // Index service
        DartsIndexService* _indexService = nullptr;
        // Userscore service
        PlayerPointService* _inputService = nullptr;
    private:
        void assembleAndSendTurnValues(const QByteArray &json);
        void subtractAndAddScoreValuesToModel(const IControllerPoint *pointModel);
        void sendWinnerJson();
        void updatePlayerPointModel(const IControllerPoint *pointModel, const int &score);
        void updatePlayerPointModel(const IControllerPoint *pointModel, const QUuid &playerId);
        QByteArray createJsonResponse(const QUuid &winnerId, const QString &winnerName);
        QByteArray createJsonResponse(const IControllerPoint* pointModel, const ControllerPlayer *playerModel, const DartsPointTurnValues* turnValues);
        QByteArray createJsonResponse(const DartsIndexes* indexes,
                                        const ControllerPlayer*playerModel,
                                        const IControllerPoint *pointModel);
        void processDomain(const int& domain,
                           const int& point, const int &score,
                           const int& modKeyCode);
        /*
         * Notify UI about controller state, current round index, undo/redo possibility and current user
         */
        void sendCurrentTurnValues();
        QString currentPlayerName()  ;
        QUuid currentPlayerId();
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
    };
}
#endif // POINTFTPCONTROLLER_H
