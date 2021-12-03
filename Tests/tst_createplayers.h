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
        auto result = _plaCtx->createPlayer(testPersonOne());
        QVERIFY(result);
    }
    void testCreatePlayerTwo(AbstractPlayersContext *_plaCtx)
    {
        auto result = _plaCtx->createPlayer(testPersonTwo());
        QVERIFY(result);
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
