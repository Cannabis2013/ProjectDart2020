#ifndef DPController_H
#define DPController_H
#include <quuid.h>
#include <qscopedpointer.h>
#include <iunaryservice.h>
#include <dpscoresservices.h>
#include "abstractdartspointcontroller.h"
#include "idpcmodel.h"
#include "dartspointturnvalues.h"
#include "idpcindexes.h"
#include "dpcservicesprovider.h"
#include "dpcjsonservices.h"

/*
 * Context abbreviations explanation:
 *  - D = Darts
 *  - C = Controller
 *  - S = Score/scores
 *  - P = Point/points
 * Ex.:
 *  - DPCContext = DartsPointControllerContext
 *  - DSCContext = DartsScoreControllerContext
 */
namespace DPCContext {
    class DPController :
            public AbstractDartsPointController,
            protected DPCServicesProvider,
            protected DPCJsonServices,
            protected DPScoresServices
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
        void beginInitialize() override;
        virtual void initializeControllerIndexes(const QByteArray& json) override;
        void initializeControllerPlayerDetails(const QByteArray &json) override;
        void initializeControllerDartsPoints(const QByteArray &json) override;
        void initializeControllerWinnerIdAndName(const QByteArray &json) override;
        void handleRequestForCurrentTournamentMetaData() override;
        void requestOrderedDartsPoints() override;
        void handleOrderedDartsPoint(const QByteArray &json) override;
        void start() override;
        void stop() override;
        void undoTurn() override;
        void redoTurn() override;
        void handleRequestFromUI() override;
        void handleAndProcessUserInput(const QByteArray &json) override;
        void handlePointAddedToDataContext(const QByteArray& json) override;
        void handleResetTournament() override;
        void undoSuccess(const QByteArray &json) override;
        void redoSuccess(const QByteArray &json) override;
    private:
        void createAndSendTurnValues(const QByteArray &json);
        void subtractAndAddScoreValuesToModel(const IDPCModel *pointModel);
        void sendWinnerJson();
        QByteArray createJsonResponse(const QUuid &winnerId, const QString &winnerName);
        QByteArray createJsonResponse(const IDPCModel* pointModel, const DCContext::IDCPlayer *playerModel,
                                      const DartsPointTurnValues* turnValues);
        QByteArray createJsonResponse(const IDPCIndexes* indexes, const DCContext::IDCPlayer *playerModel,
                                      const IDPCModel *pointModel);
        void processDomain(const int& domain,
                           const int& point, const int &score,
                           const int& modKeyCode);
        void sendCurrentTurnValues();
        QString currentPlayerName()  ;
        QUuid currentPlayerId();
        int lastPlayerIndex();
        void addPoint(const int &point, const int &score, const int &keyCode);
        void nextTurn();
        void declareWinner();
    };
}
#endif
