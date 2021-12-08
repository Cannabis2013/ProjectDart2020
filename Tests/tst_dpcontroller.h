#ifndef TST_DPCONTROLLER_H
#define TST_DPCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include <QtTest>
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
 *  But in this test section, we denote inputs witha modkey identifier (S,D,T) in front of the values
 *  that indicates the score. We keep the symbols U and R, to cover undo and redo.
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

class DPControllerTestSuite
{
public:
    DPControllerTestSuite(DartsController *ctrl) {_ctrl = ctrl;}

    void runGameOne()
    {
        /*
         * Input sequence:
         *  s = (T16,D15,S25,T12,D20,S14)
         * Expected values:
         *  S1 = 398, S2 = 411, I{post} = (2,0,0)
         */
        addInput(16,TrippleModifier);   // I : (1,0,0)/(1,0,1), S : 453/501
        addInput(15,DoubleModifier);    // I : (1,0,1)/(1,0,2), S : 423/501
        addInput(25,SingleModifer);     // I : (1,0,2)/(1,1,0), S : 398/501
        addInput(12,TrippleModifier);   // I : (1,1,0)/(1,1,1), S : 398/465
        addInput(20,DoubleModifier);    // I : (1,1,1)/(1,1,2), S : 398/425
        addInput(14,SingleModifer);     // I : (1,1,2)/(2,0,0), S : 398/411
        addInput(8,TrippleModifier);    // I : (2,0,0)/(2,0,1), S : 374/411
        addInput(12,TrippleModifier);   // I : (2,0,1)/(2,0,2), S : 338/411
        addInput(50,SingleModifer);     // I : (2,0,2)/(2,1,0), S : 288/411
        checkIndex(2,1,0);
        checkRemScores(288,411);
        resetController();
    }
    void runGameTwo()
    {
        /*
         * Input sequence:
         *  s = (T16,D15,S25,T12,D20,S14,U,U)
         * Expected values:
         *  S1 = 374, S2 = 411, I{post} = (2,0,1)
         */
        addInput(16,TrippleModifier);   // I : (1,0,0)/(1,0,1), S : 453/501
        addInput(15,DoubleModifier);    // I : (1,0,1)/(1,0,2), S : 423/501
        addInput(25,SingleModifer);     // I : (1,0,2)/(1,1,0), S : 398/501
        addInput(12,TrippleModifier);   // I : (1,1,0)/(1,1,1), S : 398/465
        addInput(20,DoubleModifier);    // I : (1,1,1)/(1,1,2), S : 398/425
        addInput(14,SingleModifer);     // I : (1,1,2)/(2,0,0), S : 398/411
        addInput(8,TrippleModifier);    // I : (2,0,0)/(2,0,1), S : 374/411
        addInput(12,TrippleModifier);   // I : (2,0,1)/(2,0,2), S : 338/411
        addInput(50,SingleModifer);     // I : (2,0,2)/(2,1,0), S : 288/411
        undoTurn();                     // I : (2,1,0)/(2,0,2), S : 338/411
        undoTurn();                     // I : (2,0,0)/(2,0,1), S : 374/411
        checkIndex(2,0,1);
        checkRemScores(374,411);
        resetController();
    }
    void runGameThree()
    {
        /*
         * Input sequence:
         *  s = (T16,D15,S25,T12,D20,S14,T8,T12,S50,U,U,U,U,R)
         * Expected values:
         *  S1 = 374, S2 = 411, I{post} = (2,0,1)
         */
        addInput(16,TrippleModifier);   // I : (1,0,0)/(1,0,1), S : 453/501
        addInput(15,DoubleModifier);    // I : (1,0,1)/(1,0,2), S : 423/501
        addInput(25,SingleModifer);     // I : (1,0,2)/(1,1,0), S : 398/501
        addInput(12,TrippleModifier);   // I : (1,1,0)/(1,1,1), S : 398/465
        addInput(20,DoubleModifier);    // I : (1,1,1)/(1,1,2), S : 398/425
        addInput(14,SingleModifer);     // I : (1,1,2)/(2,0,0), S : 398/411
        addInput(8,TrippleModifier);    // I : (2,0,0)/(2,0,1), S : 374/411
        addInput(12,TrippleModifier);   // I : (2,0,1)/(2,0,2), S : 338/411
        addInput(50,SingleModifer);     // I : (2,0,2)/(2,1,0), S : 288/411
        undoTurn();                     // I : (2,1,0)/(2,0,2), S : 338/411
        undoTurn();                     // I : (2,0,2)/(2,0,1), S : 374/411
        undoTurn();                     // I : (2,0,1)/(2,0,0), S : 398/411
        undoTurn();                     // I : (2,0,0)/(1,1,2), S : 398/425
        redoTurn();                     // I : (1,1,2)/(2,0,0), S : 398/411
        checkIndex(2,0,0);
        checkRemScores(398,411);
        resetController();
    }
    void runGameFour()
    {
        /*
         * Input sequence:
         *  s = (T20,T20,T20,T20,T20,T20,T20,T20,T20,T20,T20,T20,T19,T20,D12)
         * Expected values:
         *  S1 = 0, S2 = 141, I{post} = (3,1,0)
         */
        addInput(20,TrippleModifier);   // I : (1,0,0)/(1,0,1), S : 441/501
        addInput(20,TrippleModifier);   // I : (1,0,1)/(1,0,2), S : 381/501
        addInput(20,TrippleModifier);   // I : (1,0,2)/(1,1,0), S : 321/501
        addInput(20,TrippleModifier);   // I : (1,1,0)/(1,1,1), S : 321/441
        addInput(20,TrippleModifier);   // I : (1,1,1)/(1,1,2), S : 321/381
        addInput(20,TrippleModifier);   // I : (1,1,2)/(2,0,0), S : 321/321
        addInput(20,TrippleModifier);   // I : (2,0,0)/(2,0,1), S : 261/321
        addInput(20,TrippleModifier);   // I : (2,0,1)/(2,0,2), S : 201/321
        addInput(20,TrippleModifier);   // I : (2,0,2)/(2,1,0), S : 141/321
        addInput(20,TrippleModifier);   // I : (2,1,0)/(2,1,1), S : 141/261
        addInput(20,TrippleModifier);   // I : (2,1,1)/(2,1,2), S : 141/201
        addInput(20,TrippleModifier);   // I : (2,1,2)/(3,0,0), S : 141/141
        addInput(19,TrippleModifier);   // I : (3,0,0)/(3,0,1), S : 84/141
        addInput(20,TrippleModifier);   // I : (3,0,1)/(3,0,2), S : 24/141
        addInput(12,DoubleModifier);    // I : (3,0,2)/(3,1,0), S : 0/141
        checkIndex(3,1,0);
        checkRemScores(0,141);
        QCOMPARE(_ctrl->metaCtx()->status(),_ctrl->metaCtx()->WinnerDeclared);
        resetController();
    }
private:
    enum ModCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    void addInput(const int &point, const ModCodes &map)
    {
        _ctrl->addInput(scoreJson(point,map));
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
    QByteArray scoreJson(const int &point, const ModCodes &map)
    {
        QJsonObject obj;
        obj["point"] = point;
        obj["modKeyCode"] = map;
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
};
#endif // TST_DPCONTROLLER_H
