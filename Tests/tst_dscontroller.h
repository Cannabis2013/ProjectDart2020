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
    void addScore(const int &score)
    {
        _ctrl->addInput(scoreJson(score));
    }
    void undoTurn()
    {
        _ctrl->undoTurn();
    }
    void redoTurn()
    {
        _ctrl->redoTurn();
    }
    void resetController()
    {
        QVERIFY(_ctrl->reset());
    }
    QByteArray scoreJson(const int &score)
    {
        QJsonObject obj;
        obj["score"] = score;
        return QJsonDocument(obj).toJson();
    }
    void compareScores(const int &expScOne, const int &expScTwo)
    {
        auto remScoreOne = _ctrl->playersContext()->players().at(0).remScore;
        auto remScoreTwo = _ctrl->playersContext()->players().at(1).remScore;
        QCOMPARE(remScoreOne,expScOne);
        QCOMPARE(remScoreTwo,expScTwo);
    }
    DartsController *_ctrl;
};
#endif // TST_DSCONTROLLER_H
