#ifndef DARTSTOURNAMENTTESTSUITE_H
#define DARTSTOURNAMENTTESTSUITE_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "SignalSpyManager.h"
#include <QtTest>
#include "DartsModelsContext/Services/dartscontext.h"
class DartsTournamentTestSuite
{
public:
    enum InputModes{
        pointMode = 0x5,
        scoreMode = 0x6
    };
    enum GameModes{
        darts = 0x1,
        circular = 0x2
    };
    enum InitialPoints{
        threeHundredAndOne = 301,
        fiveHundredAndOne = 501,
        sevenHundredAndOne = 701,
        nineHundredAndOne = 901
    };
    void testCreateTournamentOne(DartsContext *_dtsCtx)
    {
        SigSpyMng spyMng(_dtsCtx,SIGNAL(tournamentCreatedOk()));
        auto ftr = spyMng.startListening();
        auto byteArray = dartsTournamentOne();
        _dtsCtx->addTournament(byteArray,{0,1});
        QVERIFY(ftr.result() != SigSpyMng::Args());
        auto tournament = _dtsCtx->dartsDbCtx()->model(0);
        QVERIFY(tournament != nullptr);
    }
    void testCreateTournamentTwo(DartsContext *_dtsCtx)
    {
        SigSpyMng spyMng(_dtsCtx,SIGNAL(tournamentCreatedOk()));
        auto ftr = spyMng.startListening();
        auto byteArray = dartsTournamentOne();
        _dtsCtx->addTournament(byteArray,{0,1});
        QVERIFY(ftr.result() != SigSpyMng::Args());
    }
    void testRemoveTournamentTwo(DartsContext *_dtsCtx)
    {
        SigSpyMng spyMng(_dtsCtx,SIGNAL(tournamentsDeleted()));
        auto ftr = spyMng.startListening(1,5000);
        _dtsCtx->deleteTournaments({1});
        auto sigs = ftr.result();
        QVERIFY(sigs != SigSpyMng::Args());
        auto model = _dtsCtx->dartsDbCtx()->model(1);
        QVERIFY(model == nullptr);
    }
private:
    QByteArray dartsTournamentOne()
    {
        QJsonObject obj;
        obj["title"] = "DSSC";
        obj["gameMode"] = darts;
        obj["inputHint"] = scoreMode;
        obj["keyPoint"] = fiveHundredAndOne;
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QByteArray dartsTournamentTwo()
    {
        QJsonObject obj;
        obj["title"] = "DPSC";
        obj["gameMode"] = darts;
        obj["inputHint"] = pointMode;
        obj["keyPoint"] = fiveHundredAndOne;
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QJsonArray toJsonArray(std::initializer_list<int> list)
    {
        QJsonArray arr;
        for (auto i = list.begin();i != list.end();i++ )
            arr.append(*i);
        return arr;
    }
};

#endif // TESTJSONDARTSBUILDER_H
