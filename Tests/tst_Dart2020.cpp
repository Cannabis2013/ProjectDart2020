#include "SignalSpyManager.h"
#include "TestJsonDartsBuilder.h"
#include "testconfiguration.h"
#ifdef LOCAL_TEST_MODE
#include <QtTest>
#include "testeventloop.h"
#include "PlayerModelsContext/createplayerscontext.h"
#include "DartsModelsContext/Services/createdartscontext.h"
#include "DartsControllerBuilder/Services/createdtsctrl.h"
#include <iostream>
#include "TestJsonPlayerBuilder.h"
using namespace std;

class backendTestSuite : public QObject
{
    Q_OBJECT
public:
    backendTestSuite()
    {
        _plaCtx = CreatePlayersContext().localJson();
        _dtsCtx = CreateDartsContext().localJson(_plaCtx);
        _dsController = CreateDtsCtrl().scoreCtrl();
        _dpController = CreateDtsCtrl().pointCtrl();
    }
    ~backendTestSuite()
    {
        if(QFile::remove("Players"))
            printf("Players file removed\n");
        if(QFile::remove("DartsData"))
            printf("DartsData file removed\n");
    }
private slots:
    void create_and_persist_KillerHertz()
    {
        SigSpyMng spyMng(_plaCtx,SIGNAL(playerAdded(bool)));
        auto ftr1 = spyMng.startListening();
        _plaCtx->createPlayer(_plaBld.testPersonOne());
        QVERIFY(ftr1.result() != SigSpyMng::Args());
        auto plaMdl = _plaCtx->playerModel(QString("Kent KillerHertz"));
        QVERIFY(plaMdl != nullptr);

    }
    void create_and_persist_Daa()
    {
        SigSpyMng spyMng(_plaCtx,SIGNAL(playerAdded(bool)));
        auto ftr = spyMng.startListening();
        _plaCtx->createPlayer(_plaBld.testPersonTwo());
        QVERIFY(ftr.result() != SigSpyMng::Args());
        auto plaMdl = _plaCtx->playerModel(QString("Jesper Daa"));
        QVERIFY(plaMdl != nullptr);
    }
    void create_darts_tournamentOne()
    {
        SigSpyMng spyMng(_dtsCtx,SIGNAL(tournamentCreatedOk()));
        auto ftr = spyMng.startListening();
        auto byteArray = _dtsBld.dartsTournamentOne();
        _dtsCtx->addTournament(byteArray,{0,1});
        QVERIFY(ftr.result() != SigSpyMng::Args());
        auto tournament = _dtsCtx->tournament(0);
        QVERIFY(tournament != nullptr);
    }
private:
    void configure()
    {
        _dtsCtx->setPlayersContext(_plaCtx);
        _dsController->setModelsContext(_dtsCtx);
        _dpController->setModelsContext(_dtsCtx);
    }
    TestJsonPlayerBuilder _plaBld;
    TestJsonDartsBuilder _dtsBld;
    PlayersContext *_plaCtx;
    DartsCtrl *_dsController;
    DartsCtrl *_dpController;
    DartsContext *_dtsCtx;
};
QTEST_GUILESS_MAIN(backendTestSuite);
#include "tst_Dart2020.moc"
#endif
