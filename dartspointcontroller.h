#ifndef DARTSPOINTSINGLEATTEMPT_H
#define DARTSPOINTSINGLEATTEMPT_H
// Proprietary QT classes
#include <quuid.h>
#include <qscopedpointer.h>
#include <iunaryservice.h>
// Custom classes
#include "abstractdartspointcontroller.h"
// Models
#include "idartscontrollerpoint.h"
#include "dartspointturnvalues.h"
#include "idartspointcontrollerindexes.h"
#include "idartscontrollerplayer.h"
// Service provider
#include "pointcontrollerserviceprovider.h"
// String definitions
#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";
namespace DartsPointControllerContext {
    class DartsPointController :
            public AbstractDartsPointController,
            protected PointControllerServiceProvider
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
        void requestOrderedDartsPoints() override;
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
    private:
        void createAndSendTurnValues(const QByteArray &json);
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
