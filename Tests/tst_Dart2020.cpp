#include "testconfiguration.h"
#include "tst_dpcontroller.h"
#ifdef LOCAL_TEST_MODE
#include <QtTest>
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
    ~BackendTestSuite() {removeData();}
private slots:
    void createAndPersistPlayerOne()
    {
        PlayersTestSuite tstSuite;
        tstSuite.testCreatePlayerOne(_plaCtx);
    }
    void createAndPersistPlayerTwo()
    {
        PlayersTestSuite tstSuite;
        tstSuite.testCreatePlayerTwo(_plaCtx);
    }
    void createDartsTournamentOne()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testCreateTournamentOne(_dtsCtx);
    }
    void createDartsTournamentTwo()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testCreateTournamentTwo(_dtsCtx);
    }
    void removeDartsTournamentTwo()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testRemoveTournamentTwo(_dtsCtx);
    }
    void createDartsTournamentThree()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testCreateTournamentTwo(_dtsCtx);
    }
    void controllerTestRunOne()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameOne();
    }
    void controllerTestRunTwo()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameTwo();
    }
    void controllerTestRunThree()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameThree();
    }
    void controllerTestRunFour()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameFour();
    }
    void controllerTestRunFive()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameFive();
    }
    void controllerTestRunSix()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->metaCtx()->Initialized);
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameSix();
    }
    void controllerTestRunSeven()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(1);
        auto result = _dpCtrl->initialize(model->id());
        QVERIFY(result == _dpCtrl->metaCtx()->Initialized);
        DPControllerTestSuite tstSuite(_dpCtrl);
        tstSuite.runGameOne();
    }
    void controllerTestRunEight()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(1);
        auto result = _dpCtrl->initialize(model->id());
        QVERIFY(result == _dpCtrl->metaCtx()->Initialized);
        DPControllerTestSuite tstSuite(_dpCtrl);
        tstSuite.runGameTwo();
    }
    void controllerTestRunNine()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(1);
        auto result = _dpCtrl->initialize(model->id());
        QVERIFY(result == _dpCtrl->metaCtx()->Initialized);
        DPControllerTestSuite tstSuite(_dpCtrl);
        tstSuite.runGameThree();
    }
    void controllerTestRunTen()
    {
        auto model = _dtsCtx->tnmDbCtx()->model(1);
        auto result = _dpCtrl->initialize(model->id());
        QVERIFY(result == _dpCtrl->metaCtx()->Initialized);
        DPControllerTestSuite tstSuite(_dpCtrl);
        tstSuite.runGameFour();
    }
private:
    void configure()
    {
        _dtsCtx->setPlayersContext(_plaCtx);
        _dsCtrl->setModelsContext(_dtsCtx);
        _dpCtrl->setModelsContext(_dtsCtx);
    }
    void removeData()
    {
        if(QFile::remove("Players"))
            printf("Players file removed\n");
        if(QFile::remove("DartsData"))
            printf("DartsData file removed\n");
    }
    PlayersContext *_plaCtx;
    DartsController *_dsCtrl;
    DartsController *_dpCtrl;
    DartsContext *_dtsCtx;
};
QTEST_GUILESS_MAIN(BackendTestSuite);
#include "tst_Dart2020.moc"
#endif
