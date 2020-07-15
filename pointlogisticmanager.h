#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <qstring.h>
#include <qlist.h>

#include "ipointlogisticmanager.h"

#define TRIPPLE "T";

const int Bull = 25;
const int BullsEye =  50;
const int trippleMultiplier = 60;
const int doubleMultiplier = 40;
namespace LogisticContext {
struct ScoreModel
{
    QList<QChar> multiplier;
    QList<int> pointValue;
};

class PointLogisticManager : public IPointLogisticManager<QString>
{
public:
    PointLogisticManager(const int &legCount = 3)
    {
        _legCount = legCount;
    }
    QString constructThrowSuggestions(const int &remainingScore, const int &turnIndex) override
    {
        auto score = new ScoreModel();

        bool isDeterministic;

        try {
            isDeterministic = pointSuggestion(remainingScore,turnIndex,score);
        } catch (std::exception *e) {
            return QString();
        }

        if (isDeterministic) {
            auto result = toString(score);
            return result;
        }

        return QString();
    }
private:
    bool pointSuggestion(int remainingScore,int turnIndex, ScoreModel *scoreObject)
    {
        /*
         * Parameter constraints:
         *  - remainingscore : [0,180}
         *  - turnIndex : [1,3]
         *  - totalTurns : [1,oo]
         */

        auto totalTurns = _legCount;

        if(remainingScore == 0)
            return true;

        if(turnIndex < 1 || turnIndex > 3)
            return false;

        if(totalTurns < turnIndex)
            return false;

        int remainingTurns = totalTurns - turnIndex;
        int p = remainingScore;

        int currentTripplePointLimit = trippleMultiplier*(remainingTurns + 1);
        int currentDoublePointLimit = doubleMultiplier*(remainingTurns + 1);
        int lowerBound = initializeLowerBound(remainingScore,doubleMultiplier);
        /*
         * The following condition filters out remaining points exceeding either 180
         * or any value which exceeds a certain threshold where a deterministic path can't be archieved
         */
        if(remainingScore > currentTripplePointLimit)
        {
            return false;
        }
        else if(remainingScore <= 20 || remainingScore == Bull || remainingScore == BullsEye)
        {
            p -= remainingScore;

            try {
                updateScoreObject('S',remainingScore,turnIndex,scoreObject);

            } catch (std::out_of_range *e) {
                throw e;
            }

            return true;
        }
        /*
         *  The following condition is mostly applicable for the first round or rounds where the remaining points is a multiplum of 3
         *
         *  The condition is met by the following relation between remaining points
         *  and thresold values calculated by the number of remaining turns and a round threshold which is a multiplum of 60 (60*(remaining rounds + 1))
         *
         *  - First turn: Remaining points must not exceed 180 points
         *  - Second turn: Remaining points must not exceed 120 points
         *  - Last turn: Remaining points must not exceed 60 points
         *
         */
        else if(remainingScore >= 20 && remainingScore <= currentTripplePointLimit && isDivisor(remainingScore,3))
        {
            p -= remainingScore >= 60 ? 60 : remainingScore;

            auto turnScore = remainingScore >= 60 ? 20 : remainingScore/3;
            try {
                updateScoreObject('T',turnScore,turnIndex,scoreObject);
                return pointSuggestion(p,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        /* The following condition is mostly applicable from the second round or rounds where the remaining points is a multiplum of 2
         * It follows the same principle as another condition where remaining points is divisble by 3
         *
         *  - First turn: Remaining points must not exceed 120 points
         *  - Second turn: Remaining points must not exceed 80 points
         *  - Last turn: Remaining points must not exceed 40 points
         */
        else if(remainingScore >= 20 && remainingScore <= currentDoublePointLimit && isDivisor(remainingScore,2))
        {
            p -= remainingScore >= 40 ? 40 : remainingScore;
            auto turnScore = remainingScore >= 40 ? 20 : remainingScore/2;

            try {
                updateScoreObject('D',turnScore,turnIndex,scoreObject);
                return pointSuggestion(p,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }

        }
        /*
         * The following condition checks if "Bullseye" is possible with the remaining points after subtraction is a multiplum of 3
         *
         * This requires remaining points in the interval [50,170]
         */
        else if(remainingScore >= 50 && remainingScore <= 170 && isDivisor(remainingScore - BullsEye,3))
         {
            p -= BullsEye;
            try {
                updateScoreObject('S',BullsEye,turnIndex,scoreObject);
                return pointSuggestion(p,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }

         }
        /*
         * The following condition checks if "Bullseye" is a possibility with the remaining points after subtraction is a multiplum of 3
         *
         * This requires remaining points to be in the interval [50,130]
         */
        else if(remainingScore >= 50 && remainingScore <= 130 && isDivisor(remainingScore - BullsEye,2))
        {
            p -= BullsEye;

            try {
                updateScoreObject('S',BullsEye,turnIndex,scoreObject);
                return pointSuggestion(p,turnIndex + 1,scoreObject);
            } catch (std::out_of_range *e) {
                throw e;
            }
        }
        else if(remainingScore - lowerBound <= 20)
        {
            auto turnScore = remainingScore - lowerBound;
            p -= turnScore;
            try {
                updateScoreObject('S',turnScore,turnIndex,scoreObject);
                return pointSuggestion(p,turnIndex + 1,scoreObject);

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

    void updateScoreObject(QChar stringIdentifier, int value, int index, ScoreModel *s)
    {
        if(index >= _legCount)
            throw new std::out_of_range("Index out of bounds");

        s->multiplier << stringIdentifier;
        s->pointValue << value;
    }

    ScoreModel *initializeModel(ScoreModel *s)
    {
        for (int i = 0; i < _legCount; ++i) {
            s->multiplier << '_';
            s->pointValue << 0;
        }

        return s;
    }

    QString toString(ScoreModel *s)
    {
        QString result;
        for (int i = 0; i < _legCount; ++i) {
            auto identifier = s->multiplier.at(i);
            auto pVal = s->pointValue.at(i);

            result += identifier == '_' ? "" : identifier + QString::number(pVal) + "-";
        }

        return result;
    }

    int _legCount;
};
}
#endif // SCORECONTROLLER_H
