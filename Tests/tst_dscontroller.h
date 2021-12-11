#ifndef TST_DSCONTROLLER_H
#define TST_DSCONTROLLER_H
#include <QtTest>
#include "DartsModelsContext/Services/dartscontext.h"
#include "DartsController/Controller/dartscontroller.h"
/*
 * Test description and notation:
 *
 *  Remaining score is denoted with 'S':
 *
 *      S : k,  k -> Integer[ 0 <= i <= 501]
 *
 *  We denote each test input sequence with 's':
 *
 *      s : (k1,k2,..,kn),  k -> Integer[0,180]
 *
 *  Furthermore, we expand the codomain of 's' with two additional symbols U and R, to cover undo and redo.
 *
 *  We denote index with 'I' and roundindex, setindex, and attemptindex, with 'R', 'S', 'A', respectively.
 *
 *      I : (R, S, A),   R,S,A -> Integer[i >= 0]
 *
 *  Example of format:
 *
 *      I{pre}/I{post} : (R1,S1,A1)/(R2,S2,A2)
 *
 *  Ex.:
 *
 *      I : (3,1,0)/(4,0,0)
 *
 *  Explanation:
 *
 *      Controller index is set with the following values before calling AbsDCIdxCtrl::next():
 *          Roundindex = 3, Setindex = 1, Attemptindex = 0
 *      After calling AbsDCIdxCtrl::next():
 *          Roundindex = 4, Setindex = 0, Attemptindex = 0
 *
 *  Pre and post definitions is also equivalent to before and after user input is added.
 */
class DSCtrlTst
{
public:
    DSCtrlTst(DartsController *ctrl, DartsContext *ctx) {
        _ctrl = ctrl;
        _ctx = ctx;
        auto status = _ctrl->initialize(_ctx->tnmDbCtx()->model(0)->id());
        QCOMPARE(status,_ctrl->metaCtx()->Initialized);
    }
    // Every method call resets controller at the end
    void runGameOne()
    {
        /*
         * Inputs:
         *  s = (50,25,12,180)
         *
         * Expected values:
         *  S1 = 439, S2 = 296, I{post} = (3,0,0)
         */
        addInput(50); // I : (1,0,0)/(1,1,0), S : 451/501
        addInput(25); // I : (1,1,0)/(2,0,0), S : 451/476
        addInput(12); // I : (2,0,0)/(2,1,0), S : 439/476
        addInput(180); // I : (2,1,0)/(3,0,0), S : 439/296
        checkRemScores(439,296);
        checkIndex(3,0,0);
        resetController();
    }
    void runGameTwo()
    {
        /*
         * Inputs:
         *  s = (5,120,12)
         *
         * Expected values:
         *  S1 = 484, S2 = 381, I{post} = (2,1,0)
         */
        addInput(5); // I : (1,0,0)/(1,1,0), S : 496/501
        addInput(120); // I : (1,1,0)/(2,0,0), S : 496/381
        addInput(12); // I : (2,0,0)/(2,1,0), S : 484/381
        checkRemScores(484,381);
        checkIndex(2,1,0);
        resetController();
    }
    void runGameThree()
    {
        /*
         * Inputs:
         *  s = (5,120,12,U)
         *
         * Expected values:
         *  S1 = 496, S2 = 381, I{post} = (2,0,0)
         */
        addInput(5); // I{pre}/I{post} : (1,0,0)/(1,1,0), S : 496/501
        addInput(120); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 496/381
        addInput(12); // I{pre}/{Ipost} : (2,0,0)/(2,1,0), S : 484/381
        undoTurn(); // I{pre}/{Ipost} : (2,1,0)/(2,0,0), S : 496/381
        checkRemScores(496,381);
        checkIndex(2,0,0);
        resetController();
    }
    void runGameFour()
    {
        /*
         * Inputs:
         *  s = (5,120,12,U,U,R)
         *
         * Expected values:
         *  S1 = 496, S2 = 381, I{post} = (2,0,0)
         */
        addInput(5); // I{pre}/{Ipost} : (1,0,0)/(1,1,0), S : 496/501
        addInput(120); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 496/381
        addInput(12); // I{pre}/{Ipost} : (2,0,0)/(2,1,0), S : 484/381
        undoTurn(); // I{pre}/{Ipost} : (2,1,0)/(2,0,0), S : 496/381
        undoTurn(); // I{pre}/{Ipost} : (2,0,0)/(1,1,0), S : 496/501
        redoTurn(); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 496/381
        checkRemScores(496,381); // Check if it compares to actual values
        checkIndex(2,0,0); // Check if it compares to actual values
        resetController();
    }
    void runGameFive()
    {
        /*
         * Inputs:
         *  s = (5,120,12,U,U,R,180)
         *
         * Expected values:
         *  S1 = 316, S2 = 381, I{post} = (2,1,0)
         */
        addInput(5); // I{pre}/{Ipost} : (1,0,0)/(1,1,0), S : 496/501
        addInput(120); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 496/381
        addInput(12); // I{pre}/{Ipost} : (2,0,0)/(2,1,0), S : 484/381
        undoTurn(); // I{pre}/{Ipost} : (2,1,0)/(2,0,0), S : 496/381
        undoTurn(); // I{pre}/{Ipost} : (2,0,0)/(1,1,0), S : 496/501
        redoTurn(); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 496/381
        addInput(180); // I{pre}/{Ipost} : (2,0,0)/(2,1,0), S : 316/381
        checkRemScores(316,381); // Check if index compares to actual index
        checkIndex(2,1,0); // Check if it compares to actual values
        resetController();
    }
    void runGameSix()
    {
        addInput(180); // I{pre}/{Ipost} : (1,0,0)/(1,1,0), S : 321/501
        addInput(180); // I{pre}/{Ipost} : (1,1,0)/(2,0,0), S : 321/321
        addInput(180); // I{pre}/{Ipost} : (2,0,0)/(2,1,0), S : 141/321
        addInput(180); // I{pre}/{Ipost} : (2,1,0)/(3,0,0), S : 141/141
        addInput(141); // I{pre}/{Ipost} : (3,0,0)/(3,1,0), S : 0/141
        checkIndex(3,1,0);
        checkRemScores(0,141);
        QVERIFY(_ctrl->metaCtx()->status() == _ctrl->metaCtx()->WinnerDeclared);
        resetController();
    }
private:
    void addInput(const int &score)
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
    void checkRemScores(const int &expScOne, const int &expScTwo)
    {
        auto remScoreOne = _ctrl->playersContext()->players().at(0).remScore;
        auto remScoreTwo = _ctrl->playersContext()->players().at(1).remScore;
        QCOMPARE(remScoreOne,expScOne);
        QCOMPARE(remScoreTwo,expScTwo);
    }
    void checkIndex(const int &roundIndex, const int &setIndex, const int &attemptIndex)
    {
        auto index = _ctrl->idxCtrl()->index();
        auto result = index.roundIndex == roundIndex &&
                index.setIndex == setIndex &&
                index.attemptIndex == attemptIndex;
        QVERIFY(result);
    }
    DartsController *_ctrl;
    DartsContext *_ctx;
};
#endif // TST_DSCONTROLLER_H
