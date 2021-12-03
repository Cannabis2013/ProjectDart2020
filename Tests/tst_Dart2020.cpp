#include "testconfiguration.h"
#ifdef LOCAL_TEST_MODE
#include <QtTest>
#include "testeventloop.h"
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
    }
    ~BackendTestSuite()
    {
        if(QFile::remove("Players"))
            printf("Players file removed\n");
        if(QFile::remove("DartsData"))
            printf("DartsData file removed\n");
    }
private slots:
    void create_and_persist_KillerHertz()
    {
        PlayersTestSuite tstSuite;
        tstSuite.testCreatePlayerOne(_plaCtx);
    }
    void create_and_persist_Daa()
    {
        PlayersTestSuite tstSuite;
        tstSuite.testCreatePlayerTwo(_plaCtx);
    }
    void create_darts_tournament_one()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testCreateTournamentOne(_dtsCtx);
    }
    void create_darts_tournament_two()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testCreateTournamentTwo(_dtsCtx);
    }
    void remove_darts_tournament_two()
    {
        DartsTournamentTestSuite tstSuite;
        tstSuite.testRemoveTournamentTwo(_dtsCtx);
    }
    void controller_test_run_one()
    {
        auto model = _dtsCtx->dartsDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->statusCodes()->initialized());
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameOne();
    }
    void controller_test_run_two()
    {
        auto model = _dtsCtx->dartsDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->statusCodes()->initialized());
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameTwo();
    }
    void controller_test_run_three()
    {
        auto model = _dtsCtx->dartsDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->statusCodes()->initialized());
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameThree();
    }
    void controller_test_run_four()
    {
        auto model = _dtsCtx->dartsDbCtx()->model(0);
        auto result = _dsCtrl->initialize(model->id());
        QVERIFY(result == _dsCtrl->statusCodes()->initialized());
        DSControllerTestSuite tstSuite(_dsCtrl);
        tstSuite.runGameFour();
    }
private:
    void configure()
    {
        _dtsCtx->setPlayersContext(_plaCtx);
        _dsCtrl->setModelsContext(_dtsCtx);
        _dpCtrl->setModelsContext(_dtsCtx);
    }
    PlayersContext *_plaCtx;
    DartsController *_dsCtrl;
    DartsController *_dpCtrl;
    DartsContext *_dtsCtx;
};
QTEST_GUILESS_MAIN(BackendTestSuite);
#include "tst_Dart2020.moc"
#endif
