#ifndef TESTJSONPLAYERBUILDER_H
#define TESTJSONPLAYERBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QtTest>
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
#include "SignalSpyManager.h"
class PlayersTestSuite
{
public:
    void testCreatePlayerOne(AbstractPlayersContext *_plaCtx)
    {
        SigSpyMng spyMng(_plaCtx,SIGNAL(playerAdded(bool)));
        auto ftr1 = spyMng.startListening();
        _plaCtx->createPlayer(testPersonOne());
        QVERIFY(ftr1.result() != SigSpyMng::Args());
        auto plaMdl = _plaCtx->playerModel(QString("Kent KillerHertz"));
        QVERIFY(plaMdl != nullptr);
    }
    void testCreatePlayerTwo(AbstractPlayersContext *_plaCtx)
    {
        SigSpyMng spyMng(_plaCtx,SIGNAL(playerAdded(bool)));
        auto ftr1 = spyMng.startListening();
        _plaCtx->createPlayer(testPersonTwo());
        QVERIFY(ftr1.result() != SigSpyMng::Args());
        auto plaMdl = _plaCtx->playerModel(QString("Jesper Daa"));
        QVERIFY(plaMdl != nullptr);
    }
private:
    QByteArray testPersonOne()
    {
        QJsonObject obj;
        obj["playerName"] = "Kent KillerHertz";
        obj["playerMail"] = "KillerHertz@gmail.com";
        return QJsonDocument(obj).toJson();
    }
    QByteArray testPersonTwo()
    {
        QJsonObject obj;
        obj["playerName"] = "Jesper Daa";
        obj["playerMail"] = "Daa@gmail.com";
        return QJsonDocument(obj).toJson();
    }
};
#endif // TSTPLABDR_H
