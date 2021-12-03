#ifndef TST_DSCONTROLLER_H
#define TST_DSCONTROLLER_H
#include <qstring.h>
#include <QtTest>
#include "DartsController/Controller/dartscontroller.h"
#include "SignalSpyManager.h"
class DSControllerTestSuite
{
public:
    DSControllerTestSuite(DartsController *ctrl) {_ctrl = ctrl;}
    // Every method call resets controller at the end
    void runGameOne()
    {
        /*
         * Throws:
         *  Player one: 50,12 / Player two: Bulls (25), T20 T20 T20 (180)
         * Expected values:
         *  Player one: 439 / Player two: 296
         */
        addScore(50);
        addScore(25);
        addScore(12);
        addScore(180);
        compareScores(439,296);
        resetController();
    }
    void runGameTwo()
    {
        /*
         * Throws:
         *  Player one: 5,12 / Player two: T20, D20, 20 (120)
         * Expected values:
         *  Player one: 484 / Player two: 381
         */
        addScore(5); // Player completely fails with this miserable throw
        addScore(120); // Player hits killer 20 (T20, D20, 20)
        addScore(12); // Player makes a crappy throw that only yields 12 points
        compareScores(484,381);
        resetController();
    }
    void runGameThree()
    {
        /*
         * Scenerio:
         *  Throws: Player one: 5,12 / Player two: T20, D20, 20 (120)
         *  Undos: Player two undos a move
         * Expected values:
         *  Player one: 484 / Player two: 381
         */
        addScore(5); // Player completely fails with this miserable throw
        addScore(120); // Player hits killer 20 (T20, D20, 20)
        addScore(12); // Player makes a crappy throw that only yields 12 points
        undoTurn();
        compareScores(496,381);
        resetController();
    }
    void runGameFour()
    {
        addScore(5); // Player completely fails with this miserable throw
        addScore(120); // Player hits killer 20 (T20, D20, 20)
        addScore(12); // Player makes a crappy throw that only yields 12 points
        undoTurn();
        undoTurn();
        redoTurn();
        compareScores(496,381);
        resetController();
    }
private:
    QFuture<QVector<QVariant>> setupListener(const char *slot, const int &sigCount, const int &waitTime)
    {
        SigSpyMng spyMng(_ctrl,slot);
        return spyMng.startListening(sigCount,waitTime); // Listen for signal emission in separate thread
    }
    void addScore(const int &score)
    {
        SigSpyMng spyMng(_ctrl,SIGNAL(updatePlayerScore(const QByteArray&))); // Listen for signal emission in separate thread
        auto ftr = spyMng.startListening(1,2000);
        _ctrl->handleInput(scoreJson(score));
        ftr.result(); // Blocking call, wait for signal emission
    }
    void undoTurn()
    {
        SigSpyMng spyMng(_ctrl,SIGNAL(updatePlayerScore(const QByteArray&))); // Listen for signal emission in separate thread
        auto ftr = spyMng.startListening(1,2000);
        _ctrl->undoTurn();
        ftr.result();
    }
    void redoTurn()
    {
        SigSpyMng spyMng(_ctrl,SIGNAL(updatePlayerScore(const QByteArray&))); // Listen for signal emission in separate thread
        auto ftr = spyMng.startListening(1,2000);
        _ctrl->redoTurn();
        ftr.result();
    }
    void resetController()
    {
        SigSpyMng spyMng(_ctrl,SIGNAL(resetSucces())); // Listen for signal emission in separate thread
        auto ftr = spyMng.startListening(1,2000);
        _ctrl->reset();
        QVERIFY(ftr.result() != SigSpyMng::Args()); // Blocking call, wait for, and verify, signal emission
    }
    QByteArray scoreJson(const int &score)
    {
        QJsonObject obj;
        obj["score"] = score;
        return QJsonDocument(obj).toJson();
    }
    void compareScores(const int &expScOne, const int &expScTwo)
    {
        auto remScoreOne = _ctrl->scoresContext()->scores().at(0).remainingScore;
        auto remScoreTwo = _ctrl->scoresContext()->scores().at(1).remainingScore;
        QCOMPARE(remScoreOne,expScOne);
        QCOMPARE(remScoreTwo,expScTwo);
    }
    DartsController *_ctrl;
};
#endif // TST_DSCONTROLLER_H
