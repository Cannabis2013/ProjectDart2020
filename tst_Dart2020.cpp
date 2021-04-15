#include "testconfiguration.h"
#ifdef LOCAL_TEST_MODE
#include <QtTest>
#include <dartapplication.h>
#include <remotemodelscontext.h>
#include "localmodelscontext.h"
#include <gamecontrollerbuilder.h>
#include <qsignalspy.h>
#include "testeventloop.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

#define DEFAULT_WAIT_TIME 750

#define Q_AWAIT(x){TestEventLoop::wait(500);}

class backendTestSuite : public QObject
{
    Q_OBJECT

public:
    backendTestSuite()
    {
        _app = DartApplication::createInstance()
                ->setModelsContextInterface(LocalModelsContext::createInstance())
                ->setControllerBuilder(new GameControllerBuilder)
                ->setup();
        QJsonObject per;
        per["playerName"] = "Per";
        per["playerMail"] = defaultPlayerMail;

        auto perJson = QJsonDocument(per).toJson();
        _app->handleCreatePlayer(perJson);
        QJsonObject jesper;
        jesper["playerName"] = "Jesper Hockey";
        jesper["playerMail"] = defaultPlayerMail;
        auto jesperJson = QJsonDocument(jesper).toJson();
        _app->handleCreatePlayer(jesperJson);
        TestEventLoop::wait(250);

    }
    ~backendTestSuite()
    {
        QFile file("Models");
        if(file.exists())
            file.remove();

        delete _app;

    }

private slots:
    void initTestCase()
    {

    }
    /*
     * Player related tests
     */
    /*
     * Create player and verify response in accordance to the following expectations:
     *  - When invoking 'handleCreatePlayer' slot, DartApplication should emit
     *    'createSendPlayer' response signal with a boolean argument which
     *    at should evaluate to true.
     */
    void test_create_player_response_succes()
    {
        QSignalSpy spy(
                    _app,
                    &DartApplication::createPlayerResponse);
        QJsonObject obj;
        obj["playerName"] = "Kent KillerHertz";
        obj["playerMail"] = "KillerHertz@outlook.dk";
        auto json = QJsonDocument(obj).toJson();
        _app->handleCreatePlayer(json);
        auto firstArgument = waitAndReturnFirstSignal(spy,DEFAULT_WAIT_TIME);
        if(firstArgument == QVariant())
            QVERIFY(false);
        auto inferedArgument = firstArgument.toBool();
        QVERIFY(inferedArgument);
    }
    /*
     * In continuation of the previous test, the given player data should be
     * contained in the list of data retrieved when invoking
     * 'requestPlayerDetails'.
     */
    void test_retrieve_player_models_succes()
    {
        QSignalSpy spy(_app,&DartApplication::sendPlayers);
        _app->requestPlayerDetails();
        // Reference player credentials
        auto userName = "Kent KillerHertz";
        auto userMail = "KillerHertz@outlook.dk";
        auto firstArgument = waitAndReturnFirstSignal(spy,DEFAULT_WAIT_TIME);
        if(firstArgument == QVariant())
            QVERIFY(false);
        auto inferedArgument = firstArgument.toList();
        auto referencePlayerPresent = false;
        for (int i = 0; i < inferedArgument.count();i += 2) {
            auto name = inferedArgument.at(i).toString();
            auto mail = inferedArgument.at(i+1).toString();
            if(name == userName && userMail == mail)
                referencePlayerPresent = true;
        }
        QVERIFY(referencePlayerPresent);
    }

    void test_delete_player_succes()
    {
        QSignalSpy spy(_app,&DartApplication::playersDeletedStatus);
        QJsonObject obj;
        obj["index"] = 2;
        auto json = QJsonDocument(obj).toJson();
        _app->handleDeletePlayer(json);
        auto firstArgument = waitAndReturnFirstSignal(spy,DEFAULT_WAIT_TIME);
        if(firstArgument == QVariant())
            QVERIFY(false);
        auto inferedArgument = firstArgument.toBool();
        QVERIFY(inferedArgument);
    }

    void test_create_tournament_succes()
    {
        QSignalSpy spy(_app,&DartApplication::tournamentAssembledAndStored);
        auto title = "Slyngelstuen";
        auto gameMode = 0x1;
        auto keyPoint = 501;
        auto winKeyCode = 0x2B;
        auto displayHint = 0x4;
        auto inputHint = 0x6;
        auto attempts = 1;
        QJsonObject obj;
        obj["Title"] = title;
        obj["GameMode"] = gameMode;
        obj["KeyPoint"] = keyPoint;
        obj["TerminalKeyCode"] = winKeyCode;
        obj["DisplayHint"] = displayHint;
        obj["InputHint"] = inputHint;
        obj["Attempts"] = attempts;
        QJsonArray arr = {0,1};
        obj["PlayerIndexes"] = arr;
        auto json = QJsonDocument(obj).toJson();
        _app->handleFTPDetails(json);
        auto firstArgument = waitAndReturnFirstSignal(spy,DEFAULT_WAIT_TIME);
        auto inferedArgument = firstArgument.toBool();
        QVERIFY(inferedArgument);
    }
private:

    QVariant waitAndReturnFirstSignal(QSignalSpy& spy, const int& ms)
    {
        // Block in case of async behaviour
        TestEventLoop::wait(ms);
        // Assert false if no signals emitted; otherwise proceed
        if(spy.count() <= 0)
            return QVariant();
        // Take the first signal arguments
        auto sigs = spy.takeFirst();
        auto firstArgument = sigs.first();
        return firstArgument;
    }

    const QString defaultPlayerMail = "DefaultSucker@gmail.com";
    DartApplication* _app;
};
QTEST_GUILESS_MAIN(backendTestSuite);
#include "tst_Dart2020.moc"
#endif
