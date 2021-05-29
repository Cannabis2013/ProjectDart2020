#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H
// Proprietary QT classes
#include <quuid.h>
// Custom classes
#include "abstractdartsscorecontroller.h"
#include "idartslogisticsservice.h"
#include "iscorevalidator.h"
#include "idartsmultiattemptindexservice.h"
#include "iplayerscoreservice.h"
#include "idartsscorejsonbuilderservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartscontrollerscore.h"
#include "dartsscoreturnvalues.h"
#include "iternaryservice.h"
#include "idartsmodelsbuilderservice.h"
#include "idartscontrollerindexesbuilder.h"
#include "idartsjsonextractor.h"
// Definitions
#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

using namespace std;

namespace DartsScoreMultiAttemptContext
{
    class DartsScoreMultiAttempt : public AbstractDartsScoreController
    {
        Q_OBJECT
    public:
        // Public types
        enum InputDomains {
            PointDomain = 0x01,
            CriticalDomain = 0x02,
            OutsideDomain = 0x03,
            TargetDomain = 0x4,
            InputOutOfRange = 0x5
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
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ControllerScore;
        typedef QVector<const ControllerScore*> DartsScores;
        typedef QVector<const IDartsPlayer*> IDartsPlayers;
        typedef IPlayerScoreService<ControllerScore> PlayerScoreService;
        typedef IDartsScoreJsonBuilderService<ControllerScore,IDartsMultiAttemptIndexes,QByteArray,QString> MultiAttemptJsonService;
        typedef IBinaryService<const IDartsLogisticsService<QString>*,const int&, QString> LogisticService;
        typedef ITernaryService<const IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>*,
                                const IPlayerScoreService<ControllerScore>*,
                                const IDartsLogisticsService<QString>*,
                                const DartsScoreTurnValues*> DartsScoreTurnValuesBuilderService;
        typedef IDartsModelsBuilderService<ControllerScore,QByteArray,PlayerScoreService,
                                           QUuid,QString> DartsScoreBuilderService;
        typedef IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes> DartsIndexService;
        typedef IDartsControllerIndexesBuilder<IDartsMultiAttemptIndexes,DartsIndexService,QByteArray> IndexesBuilderService;
        typedef IDartsJsonExtractor<QByteArray,QString> JsonExtractorService;
        // Create instance of LocalFTPController
        static DartsScoreMultiAttempt* createInstance(const QUuid &tournament);
        /*
         * Get/set evaluator service
         */
        DartsScoreMultiAttempt *setInputValidator(IScoreValidator *scoreEvaluator);
        DartsScoreMultiAttempt *setIndexController(IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>*indexController);
        DartsScoreMultiAttempt *setScoreController(PlayerScoreService *scoreController);
        /*
         * Point suggestion section
         */
        IDartsLogisticsService<QString> *pointLogisticInterface() const;
        DartsScoreMultiAttempt* setLogisticInterface(IDartsLogisticsService<QString> *pointLogisticInterface);
        DartsScoreMultiAttempt* setJsonService(MultiAttemptJsonService *jsonService);
        DartsScoreMultiAttempt* setAssembleDartsPlayersByJson(IUnaryService<const QByteArray &, IDartsPlayers> *service);
        DartsScoreMultiAttempt* setAssembleDartsPlayerByJson(IUnaryService<const QByteArray &, const IDartsPlayer *> *service);
        DartsScoreMultiAttempt* setDetermineControllerStateByWinnerId(IUnaryService<const QUuid &, int> *service);
        DartsScoreMultiAttempt* setAddAccumulatedScoreToModel(IBinaryService<const ControllerScore *,
                                                                             const int&,
                                                                             const ControllerScore *> *service);
        DartsScoreMultiAttempt* setAssembleDartsScoreTurnValues(DartsScoreTurnValuesBuilderService *service);
        DartsScoreMultiAttempt* setDartsScoreBuilderService(DartsScoreBuilderService *service);
        DartsScoreMultiAttempt* setDartsIndexesBuilderService(IndexesBuilderService *newDartsIndexesBuilderService);
        DartsScoreMultiAttempt* setDartsJsonExtractorService(JsonExtractorService *newDartsJsonExtractorService);

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
        void assembleMultiAttemptDartsScores() override;
        void handleRequestDartsScores() override;
        /*
         * Models context has persisted score succesfully
         */
        void handleScoreAddedToDataContext(const QByteArray& json) override;
        /*
         * Reinitialize controller
         *  - Set controller back to its original state
         */
        void handleResetTournament() override;
        // Get current status
        int currentStatus() const;
        /*
         * Recieve darts index values, score values, and player values from modelscontext
         */
        virtual void initializeControllerIndexes(const QByteArray& json) override;
        void initializeControllerPlayerDetails(const QByteArray &json) override;
        void initializeControllerDartsScores(const QByteArray &json) override;
        void initializeControllerWinnerIdAndName(const QByteArray &json) override;
        /*
         * Handle undo/redo response
         */
        void undoSuccess(const QByteArray &json) override;
        void redoSuccess(const QByteArray &json) override;
    private:
        /*
         * Private constructor
         */
        DartsScoreMultiAttempt(const QUuid &tournament)
        {
            _tournament = tournament;
        }
        /*
         * Check if controller is busy doing something else
         */
        bool isBusy();
        void processDomain(const int& domain, const int &score);
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
        void addScore(const int &score);
        /*
         * Index manipulating methods
         */
        void nextTurn();
        void declareWinner();
        // Member variables
        QUuid _tournament = QUuid();
        int _currentStatus = ControllerState::NotInitialized;
        //Services
        // Generate throwsuggestions
        IDartsLogisticsService<QString> *_scoreLogisticInterface = nullptr;
        // Validator service
        IScoreValidator* _scoreEvaluator = nullptr;
        // Index service
        DartsIndexService* _indexController = nullptr;
        // Userscore service
        PlayerScoreService* _scoreController = nullptr;
        MultiAttemptJsonService* _dartsJsonBuilderService;
        // Builder services
        DartsScoreBuilderService* _dartsScoreBuilderService;
        IndexesBuilderService* _dartsIndexesBuilderService;
        // Json services
        JsonExtractorService* _dartsJsonExtractorService;
        IUnaryService<const QByteArray&,const IDartsPlayer*>* _assembleDartsPlayerByJson;
        IUnaryService<const QByteArray&, IDartsPlayers>* _assembleDartsPlayersByJson;
        IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
        IBinaryService<const ControllerScore*, const int&,const ControllerScore*>* _addAccumulatedScoreToModel;
        DartsScoreTurnValuesBuilderService* _assembleDartsScoreTurnValues;
    };
};


#endif // FIVEHUNDREDANDONEGAME_H
