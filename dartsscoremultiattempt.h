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
#include "idartsmultiattemptjsonservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "dartsscore.h"
#include "dartsscoreturnvalues.h"
#include "iternaryservice.h"
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
        typedef QVector<const DartsScore*> DartsScores;
        typedef QVector<const IDartsPlayer*> IDartsPlayers;
        typedef IPlayerScoreService<DartsScore> PlayerScoreService;
        typedef IDartsMultiAttemptJsonService<PlayerScoreService> MultiAttemptJsonService;
        typedef IBinaryService<const IDartsLogisticsService<QString>*,const int&, QString> LogisticService;
        typedef ITernaryService<const IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>*,
                                const IPlayerScoreService<DartsScore>*,
                                const IDartsLogisticsService<QString>*,
                                const DartsScoreTurnValues*> DartsScoreTurnValuesBuilderService;
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
        DartsScoreMultiAttempt* setAssembleDartsScoreByJsonService(IUnaryService<const QByteArray &, const DartsScore *> *newAssembleDartsScoreByJsonService);
        DartsScoreMultiAttempt* setAssembleDartsScoresByJsonService(IUnaryService<const QByteArray &, DartsScores> *newAssembleDartsScoresByJsonService);
        DartsScoreMultiAttempt* setAssembleDartsPlayersByJson(IUnaryService<const QByteArray &, IDartsPlayers> *newAssembleDartsPlayersByJson);
        DartsScoreMultiAttempt* setAssembleDartsPlayerByJson(IUnaryService<const QByteArray &, const IDartsPlayer *> *newAssembleDartsPlayerByJson);
        DartsScoreMultiAttempt* setDetermineControllerStateByWinnerId(IUnaryService<const QUuid &, int> *newDetermineControllerStateByWinnerId);
        DartsScoreMultiAttempt* setAssembleDartsScoreIndexesByJson(IUnaryService<const QByteArray &, const IDartsMultiAttemptIndexes*> *newAssembleDartsScoreIndexesByJson);
        DartsScoreMultiAttempt* setAddAccumulatedScoreToModel(IBinaryService<const DartsScore *, const int&, const DartsScore *> *newAddAccumulatedScoreToModel);
        DartsScoreMultiAttempt* setAssembleDartsScoreTurnValues(DartsScoreTurnValuesBuilderService *newAssembleDartsScoreTurnValues);

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
        void addPoint(const int &score);
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
        IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>* _indexController = nullptr;
        // Userscore service
        PlayerScoreService* _scoreController = nullptr;
        MultiAttemptJsonService* _jsonService;
        // Json services
        IUnaryService<const QByteArray&, const DartsScore*>* _assembleDartsScoreByJsonService;
        IUnaryService<const QByteArray&, DartsScores>* _assembleDartsScoresByJsonService;
        IUnaryService<const QByteArray&,const IDartsPlayer*>* _assembleDartsPlayerByJson;
        IUnaryService<const QByteArray&, IDartsPlayers>* _assembleDartsPlayersByJson;
        IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
        IUnaryService<const QByteArray&,const IDartsMultiAttemptIndexes*>* _assembleDartsScoreIndexesByJson;
        IBinaryService<const DartsScore*, const int&,const DartsScore*>* _addAccumulatedScoreToModel;
        DartsScoreTurnValuesBuilderService* _assembleDartsScoreTurnValues;
    };
};


#endif // FIVEHUNDREDANDONEGAME_H
