#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <qstring.h>
#include <qlist.h>

#include "ipointlogisticinterface.h"

#define TRIPPLE "T";

const int Bull = 25;
const int BullsEye =  50;
const int singleMaxValue = 20;
const int doubleMaxValue = 40;
const int trippleMaxValue = 60;

struct ScoreModel
{
    QVector<char> multiplier;
    QVector<int> pointValue;
};

class PointLogisticManager : public IPointLogisticInterface<QString>
{
public:

    /*
     * Public types
     */
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    /*
     * Constructor
     */
    PointLogisticManager(const int &throwCount = 3)
    {
        _throwCount = throwCount;
    }
    QString constructThrowSuggestions(const int &remainingScore, const int &turnIndex) override
    {
        auto score = new ScoreModel();

        score->multiplier = QVector(_throwCount,'\0');
        score->pointValue = QVector(_throwCount,0);

        bool hasADeterminedPath;

        try {
            hasADeterminedPath = pointSuggestion(remainingScore,turnIndex,score);
        } catch (std::exception *e) {
            return QString();
        }

        if (hasADeterminedPath) {
            auto result = toString(score);
            return result;
        }

        return QString();
    }
    void setNumberOfThrows(const int &throwCount) override
    {
        _throwCount = throwCount;
    }

    void setLastThrowKeyCode(const int &keyCode) override
    {
        _lastThrowKeyCode = keyCode;
    }
    int lastThrowKeyCode() override
    {
        return _lastThrowKeyCode;
    }
private:
    bool pointSuggestion(const int &remainingScore,const int &turnIndex, ScoreModel *scoreObject)
    {
        /*
         * Parameter constraints:
         *  - If endgame condition modifier is equal to "double"
         *      > remainingscore : [0,160}
         *  - else if engame condition modifier is equal to "tripple
         *      > remainingscore : [0,180}
         *  - else
         *      > remainingscore : [0,140}
         *  - turnIndex : [1,3]
         *  - totalTurns : [1,oo]
         */

        auto totalTurns = _throwCount;

        if(remainingScore == 0)
            return true;

        if(turnIndex < 1 || turnIndex > 3)
            return false;

        if(totalTurns < turnIndex)
            return false;

        int lastThrowMaxValue = _lastThrowKeyCode == KeyMappings::DoubleModifier ? doubleMaxValue :
                                                                                   trippleMaxValue;
        int remainingTurns = totalTurns - turnIndex;
        int newScore = remainingScore;

        int currentTripplePointLimit = trippleMaxValue*(remainingTurns) + lastThrowMaxValue;
        int currentDoublePointLimit = doubleMaxValue*(remainingTurns) + lastThrowMaxValue;
        int lowerBound = initializeLowerBound(remainingScore,doubleMaxValue);
        /*
         * The following condition filters out remaining points exceeding either 180/160/140
         *  or any value that exceeds the range, in which a determined path can't be made
         *  within compliance of the terminating keycode condition.
         */
        if(remainingScore > currentTripplePointLimit)
        {
            return false;
        }
        else if(remainingTurns == 0 &&
                _lastThrowKeyCode == KeyMappings::SingleModifer &&
                remainingScore >= singleMaxValue &&
                remainingScore != Bull &&
                remainingScore != BullsEye)
        {
            return false;
        }
        else if(remainingTurns == 0 &&
                _lastThrowKeyCode == KeyMappings::DoubleModifier &&
                remainingScore >= doubleMaxValue)
        {
            return false;
        }
        else if(remainingTurns == 0 &&
                _lastThrowKeyCode == KeyMappings::TrippleModifier &&
                remainingScore >= trippleMaxValue)
        {
            return false;
        }

        /*
         * The following blocks checks if the players remaining points is within striking range,
         *  which means that a winning shot, that complies with the last keycode condition, can be made.
         */

        if((remainingScore <= 20 ||
            remainingScore == Bull ||
            remainingScore == BullsEye) &&
            _lastThrowKeyCode == KeyMappings::SingleModifer)
        {
            newScore -= remainingScore;

            try {
                updateScoreObject('S',remainingScore,turnIndex,scoreObject);
                return true;

            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        else if(remainingScore <= doubleMaxValue &&
                isDivisor(remainingScore,2) &&
                _lastThrowKeyCode == KeyMappings::DoubleModifier)
        {
            newScore -= remainingScore;
            auto scoreValue = remainingScore/2;

            try {
                updateScoreObject('D',scoreValue,turnIndex,scoreObject);
                return true;

            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        else if(remainingScore <= trippleMaxValue &&
                isDivisor(remainingScore,3) &&
                _lastThrowKeyCode == KeyMappings::TrippleModifier)
        {
            newScore -= remainingScore;
            auto scoreValue = remainingScore/3;

            try {
                updateScoreObject('T',scoreValue,turnIndex,scoreObject);
                return true;

            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        /*
         *  The following condition is mostly for the first round,
         *  or rounds where the remaining points is a multiplum of 3
         *
         *  The condition is met by the following relation between the remaining points
         *  and the thresold values calculated by the number of remaining turns and a round threshold, which is a multiplum of 60 (60*(remaining rounds + 1))
         *
         *  - First turn: Remaining points must not exceed 180/160/140 points
         *  - Second turn: Remaining points must not exceed 120/100/80 points
         *  - Last turn: Remaining points must not exceed 60/40/20 points
         *
         */
        else if(remainingScore >= singleMaxValue && remainingScore <= currentTripplePointLimit && isDivisor(remainingScore,3))
        {
            newScore -= remainingScore >= trippleMaxValue ? trippleMaxValue : remainingScore;
            auto turnScore = remainingScore >= trippleMaxValue ? singleMaxValue : remainingScore/3;
            try {
                updateScoreObject('T',turnScore,turnIndex,scoreObject);
                return pointSuggestion(newScore,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        /* The following condition is mostly applicable from the second round,
         *  or rounds where the remaining points is a multiplum of 2
         *
         * It follows the same principle as the other condition where remaining points is divisible by 3
         *
         *  - First turn: Remaining points must not exceed 140/120 points
         *  - Second turn: Remaining points must not exceed 80 points
         *  - Last turn: Remaining points must not exceed 40/60 points
         */
        else if(remainingScore >= singleMaxValue && remainingScore <= currentDoublePointLimit && isDivisor(remainingScore,2))
        {
            newScore -= remainingScore >= doubleMaxValue ? doubleMaxValue : remainingScore;
            auto turnScore = remainingScore >= doubleMaxValue ? singleMaxValue : remainingScore/2;
            try {
                updateScoreObject('D',turnScore,turnIndex,scoreObject);
                return pointSuggestion(newScore,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        /*
         * The following condition checks if "Bullseye" is a possibility, which requires the remaining points, after subtraction,
         *  to be a multiplum of 3
         *
         * The points must be in the interval [50,170]
         */
        else if(remainingScore >= 50 && remainingScore <= 170 && isDivisor(remainingScore - BullsEye,3))
         {
            newScore -= BullsEye;
            try {
                updateScoreObject('S',BullsEye,turnIndex,scoreObject);
                return pointSuggestion(newScore,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
         }
        /*
         * The following condition checks if "Bullseye" is a possibility. It follows that the remaining points,
         *  after subtraction, must be a multiplum of 2
         *
         * This requires remaining points to be in the interval [50,130]
         */
        else if(remainingScore >= 50 && remainingScore <= 130 && isDivisor(remainingScore - BullsEye,2))
        {
            newScore -= BullsEye;

            try {
                updateScoreObject('S',BullsEye,turnIndex,scoreObject);
                return pointSuggestion(newScore,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        else if(remainingScore - lowerBound <= 20)
        {
            auto turnScore = remainingScore - lowerBound;
            newScore -= turnScore;
            try {
                updateScoreObject('S',turnScore,turnIndex,scoreObject);
                return pointSuggestion(newScore,turnIndex + 1,scoreObject);

            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        else
        {
            return false;
        }
    }

    int initializeLowerBound(int remainingScore, int multiplier)
    {
        if(remainingScore < multiplier)
            return 0;

        auto rest = remainingScore % multiplier;

        return remainingScore - rest;
    }

    bool isDivisor(int base, int div)
    {
        if(base == 0 || div == 0)
            throw new std::domain_error("One of operands zero");

        return base % div == 0;
    }

    void updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s)
    {
        if(value < 0)
            throw new std::out_of_range("Value out of bounds");

        s->multiplier[index - 1] = stringIdentifier;
        s->pointValue[index - 1] = value;
    }

    QString toString(ScoreModel *s)
    {
        QString result;
        for (int i = 0; i < _throwCount; ++i) {
            auto identifier = s->multiplier.at(i);
            auto pVal = s->pointValue.at(i);
            result += identifier == '\0' ? "" : identifier + QString::number(pVal) + "  ";
        }

        return result;
    }

    int _throwCount;
    int _lastThrowKeyCode;
};
#endif // SCORECONTROLLER_H


