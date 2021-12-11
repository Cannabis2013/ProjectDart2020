#include "testconfiguration.h"
#ifdef LOCAL_TEST_MODE
#include <QtTest>
#include "tst_dpcontroller.h"
#include "PlayerModelsContext/createplayerscontext.h"
#include "DartsModelsContext/Services/createdartscontext.h"
#include "DartsControllerBuilder/Services/createdtsctrl.h"
#include <iostream>
#include "tst_createplayers.h"
#include "tst_dscontroller.h"
#include "tst_dartstournaments.h"
class BackendTestSuite : public QObject
{
    Q_OBJECT
public:
    BackendTestSuite()
    {
        _plaCtx = CreatePlayersContext().localJson();
        _dtsCtx = CreateDartsContext().localJson(_plaCtx);
        _dsCtrl = CreateDtsCtrl().scoreCtrl();
        _dpCtrl = CreateDtsCtrl().pointCtrl();
        configure();
        removeData(); // Remove data that failed clean up from previous test
    }
private slots:
    void cleanupTestCase() {removeData();}
    void createAndPersistPlayerOne() {PlayersTestSuite().testCreatePlayerOne(_plaCtx);}
    void createAndPersistPlayerTwo() {PlayersTestSuite().testCreatePlayerTwo(_plaCtx);}
    void createDartsTournamentOne() {DartsTournamentTestSuite().testCreateTournamentOne(_dtsCtx);}
    void createDartsTournamentTwo() {DartsTournamentTestSuite().testCreateTournamentTwo(_dtsCtx);}
    void removeDartsTournamentTwo() {DartsTournamentTestSuite().testRemoveTournamentTwo(_dtsCtx);}
    void createDartsTournamentThree() {DartsTournamentTestSuite().testCreateTournamentTwo(_dtsCtx);}
    void ctrlTstRunOne() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameOne();}
    void ctrlTstRunTwo() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameTwo();}
    void ctrlTstRunThree() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameThree();}
    void ctrlTstRunFour() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameFour();}
    void ctrlTstRunFive() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameFive();}
    void ctrlTstRunSix() {DSCtrlTst(_dsCtrl,_dtsCtx).runGameSix();}
    void ctrlTstRunSeven() {DPCtrlTst(_dpCtrl,_dtsCtx).runGameOne();}
    void ctrlTstRunEight() {DPCtrlTst(_dpCtrl,_dtsCtx).runGameTwo();}
    void ctrlTstRunNine() {DPCtrlTst(_dpCtrl,_dtsCtx).runGameThree();}
    void ctrlTstRunTen() {DPCtrlTst(_dpCtrl,_dtsCtx).runGameFour();}
private:
    void configure()
    {
        _dtsCtx->setPlayersContext(_plaCtx);
        _dsCtrl->setModelsContext(_dtsCtx);
        _dpCtrl->setModelsContext(_dtsCtx);
    }
    void removeData()
    {
        if(QFile::remove("Players")) printf("Players file removed\n");
        if(QFile::remove("DartsData")) printf("DartsData file removed\n");
    }
    PlayersContext *_plaCtx;
    DartsController *_dsCtrl;
    DartsController *_dpCtrl;
    DartsContext *_dtsCtx;
};
QTEST_GUILESS_MAIN(BackendTestSuite);
#include "tst_Dart2020.moc"
#endif
