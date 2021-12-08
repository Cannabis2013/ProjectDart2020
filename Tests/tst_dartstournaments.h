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
        auto byteArray = dartsTournamentOne();
        _dtsCtx->addTournament(byteArray,{0,1});
        auto tournament = _dtsCtx->tnmDbCtx()->model(0);
        QVERIFY(tournament != nullptr);
    }
    void testCreateTournamentTwo(DartsContext *_dtsCtx)
    {
        auto byteArray = dartsTournamentOne();
        auto result = _dtsCtx->addTournament(byteArray,{0,1});
        QVERIFY(result);
        auto tournament = _dtsCtx->tnmDbCtx()->model(1);
        QVERIFY(tournament != nullptr);
    }
    void testRemoveTournamentTwo(DartsContext *_dtsCtx)
    {
        auto result = _dtsCtx->deleteTournaments({1});
        QVERIFY(result);
        auto tournament = _dtsCtx->tnmDbCtx()->model(1);
        QVERIFY(tournament == nullptr);
    }
private:
    QByteArray dartsTournamentOne()
    {
        QJsonObject obj;
        obj["title"] = "DSSC";
        obj["gameMode"] = darts;
        obj["inputHint"] = scoreMode;
        obj["initRemScore"] = fiveHundredAndOne;
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QByteArray dartsTournamentTwo()
    {
        QJsonObject obj;
        obj["title"] = "DPSC";
        obj["gameMode"] = darts;
        obj["inputHint"] = pointMode;
        obj["initRemScore"] = fiveHundredAndOne;
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
