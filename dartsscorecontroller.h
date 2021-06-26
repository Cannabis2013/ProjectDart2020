#ifndef DARTSSCORECONTROLLER_H
#define DARTSSCORECONTROLLER_H
// Proprietary QT classes
#include <quuid.h>
// Custom classes
#include "abstractdartsscorecontroller.h"
#include "idartsinputsuggestion.h"
#include "iscorevalidator.h"
#include "idartsscoreindexservice.h"
#include "iplayerscoreservice.h"
#include "idartsscorejsonbuilderservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartscontrollerscore.h"
#include "dartsscoreturnvalues.h"
#include "iternaryservice.h"
#include "idartsmodelsbuilderservice.h"
#include "idartscontrollerindexesbuilder.h"
#include "idartsplayerbuilderservice.h"
#include "ibytearrayjsonmerger.h"
#include "ibuilddartsscorecontrollervalues.h"
#include "iaddscoretodartsscoremodel.h"
#include "iqtjsonbuilder.h"
#include "iqtjsonextractor.h"
// Definitions
#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

using namespace std;

namespace DartsScoreControllerContext
{
    class DartsScoreController : public AbstractDartsScoreController
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
            WinnerDeclared = 0x15
        };
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ControllerScore;
        typedef QVector<const ControllerScore*> DartsScores;
        typedef IDartsPlayer<QUuid,QString> DartsPlayer;
        typedef QVector<const DartsPlayer*> DartsPlayers;
        typedef IPlayerScoreService<DartsPlayer,ControllerScore> PlayerScoreService;
        typedef IDartsScoreControllerIndexes<QByteArray> ControllerIndexes;
        typedef IDartsScoreJsonBuilderService<ControllerScore,ControllerIndexes,QByteArray,QString> DartsScoreJsonService;
        typedef IBinaryService<const IDartsInputSuggestion<QString>*,const int&, QString> LogisticService;
        typedef IDartsModelsBuilderService<ControllerScore,QByteArray,PlayerScoreService,
                                           QUuid,QString> DartsScoreBuilderService;
        typedef IDartsScoreIndexService<ControllerIndexes> DartsIndexService;
        typedef IDartsControllerIndexesBuilder<ControllerIndexes,DartsIndexService,QByteArray> IndexesBuilderService;
        typedef IDartsPlayerBuilderService<DartsPlayer,QUuid,QString,QByteArray> PlayerBuilderService;
        // Create instance of LocalFTPController
        static DartsScoreController* createInstance(const QUuid &tournament, const int &displayHint);
        /*
         * Point suggestion section
         */
        IDartsInputSuggestion<QString> *pointLogisticInterface() const;
    public slots:
        /*
         * Handle wake up request
         *  - Set status to 'InitializedAndReady'
         *  - Transmit 'ready' response
         */
        void beginInitialize() override;
        /*
         * Recieve darts index values, score values, and player values from modelscontext
         */
        virtual void initializeControllerIndexes(const QByteArray& json) override;
        void initializeControllerPlayerDetails(const QByteArray &json) override;
        void initializeControllerDartsScores(const QByteArray &json) override;
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
         * Send current tournament id
         */
        void handleRequestForCurrentTournamentMetaData() override;
        /*
         * Handle request for playerscores
         *
         * The following methods is called dependently on input hint
         */
        void assembleOrderedDartsScores() override;
        void handleRequestDartsScores() override;
        /*
         * Handle status request from UI
         */
        void handleRequestFromUI() override;
        /*
         * Handle and Evaluate input from user
         */
        void handleAndProcessUserInput(const QByteArray &json) override;
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
         * Handle undo/redo response
         */
        void undoSuccess(const QByteArray &json) override;
        void redoSuccess(const QByteArray &json) override;
    protected:
        /*
         * Protected constructor
         */
        DartsScoreController(const QUuid &tournament, const int &displayHint);
        //Services
        // Generate throwsuggestions
        IDartsInputSuggestion<QString> *_scoreLogisticInterface = nullptr;
        // Validator service
        IScoreValidator* _inputEvaluator = nullptr;
        // Index service
        DartsIndexService* _indexService = nullptr;
        // Userscore service
        PlayerScoreService* _inputService = nullptr;
        DartsScoreJsonService* _dartsJsonBuilderService;
        // Builder services
        DartsScoreBuilderService* _dartsScoreBuilder;
        IndexesBuilderService* _dartsIndexesBuilderService;
        PlayerBuilderService* _playerBuilderService;
        IUnaryService<const QUuid&,int>* _determineControllerStateByWinnerId;
        IAddScoreToDartsScoreModel* _addTotalScoreToModel;
        IBuildDartsScoreControllerValues* _turnValuesBuilder;
        IByteArrayJsonMerger* _jsonMergeService;
        // Json services
        IQtJsonBuilder *_dartsJsonBuilder;
        IQtJsonExtractor *_extractJson;
    private:
        void assembleAndSendTurnValues(const QByteArray &json);
        void assembleAndSendWinnerValues();
        void subtractAndAddScoreToModel(const ControllerScore *scoreModel);
        QByteArray createJsonResponse(const QUuid &winnerId, const QString &winnerName);
        QByteArray createJsonResponse(const ControllerScore* scoreModel, const DartsScoreTurnValues* turnValues);
        QByteArray createJsonResponse(const ControllerScore* scoreModel, const ControllerIndexes* indexes, const DartsPlayer *playerModel);
        /*
         * Check if controller is busy doing something else
         */
        void processDomain(const int& domain, const int &score);
        /*
         * Notify UI about controller state, current round index, undo/redo possibility and current user
         */
        void sendCurrentTurnValues();
        QString currentPlayerName()  ;
        QUuid currentPlayerId();
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
        int _displayHint;
        QUuid _tournamentId = QUuid();
        int _status = 0x0;
    };
};


#endif // FIVEHUNDREDANDONEGAME_H
