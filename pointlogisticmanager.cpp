#include "pointlogisticmanager.h"

bool PointLogisticManager::pointSuggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject)
{
    auto totalTurns = _throwCount;
    int remainingTurns = totalTurns - turnIndex;
    /*
     * Evaluate constrains
     */
    if(!evaluteConstraints(remainingScore,turnIndex,totalTurns))
        return false;
    /*
     * The terminal state
     *
     * The algorithm checks if the remaining score is below the terminal threshold, and if that's the case,
     *  how to get to the terminal point. If not, the algorithm proceeds to find another way to reach terminal state.
     */
    if(remainingScore <= _terminalThreshold)
        return isWithinTerminalThreshold(remainingScore,turnIndex,scoreObject);
    else if(remainingTurns == 0 && remainingScore != BullsEye)
        return false;
    /*
     * This is the pathfinding state where the algorithm tries to determine, if exists, the route.
     * If this is the last round, no ways exists, and the algorithm terminates with false.
     */
    if(remainingScore == BullsEye)
        return writeToScoreObject(remainingScore,BullsEye,singleDivisor,turnIndex,scoreObject);
    else if(remainingScore >= upperThresholdValue && turnIndex == 1)
        return determineRouteByThresholdDiff(remainingScore,turnIndex,scoreObject);
    else
        return determineRouteByDiff(remainingScore,turnIndex,scoreObject);
}

bool PointLogisticManager::evaluteConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns)
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
    if(remainingScore > 170 || remainingScore <= 0)
        return false;
    else if(turnIndex < 1 || turnIndex > 3)
        return false;
    else if(totalTurns < turnIndex)
        return false;
    else
        return true;
}

QString PointLogisticManager::constructThrowSuggestions(const int &remainingScore, const int &turnIndex)
{
    auto score = new ScoreModel();

    score->multiplier = QVector<char>(_throwCount,'\0');
    score->pointValue = QVector<int>(_throwCount,0);

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

QString PointLogisticManager::toString(ScoreModel *s)
{
    QString result;
    for (int i = 0; i < _throwCount; ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + "  ";
    }

    return result;
}

bool PointLogisticManager::isWithinTerminalThreshold(const int &remainingScore,
                                                     const int &turnIndex,
                                                     ScoreModel *scoreObject)
{
    auto newScore = remainingScore;
    if(isDivisor(remainingScore,_terminalDivisor))
    {
        newScore -= remainingScore;
        auto turnScore = remainingScore/_terminalDivisor;
        try {
            auto identifier = identifiers[_terminalDivisor - 1];
            updateScoreObject(identifier,turnScore,turnIndex,scoreObject);
            return true;
        } catch (std::out_of_range *e) {
            throw e;
        }
    }
    else
    {
        for (int i = singleMaxValue; i > 0; --i) {
            auto endScore = remainingScore - i;
            if(endScore < _terminalThreshold && endScore > 0  && endScore % _terminalDivisor == 0)
            {
                newScore -= i;
                try {
                    updateScoreObject('S',i,turnIndex,scoreObject);
                    return pointSuggestion(newScore,turnIndex + 1,scoreObject);
                }  catch (const char *e) {
                    throw e;
                }
            }
        }
    }
    return false;
}

bool PointLogisticManager::determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex,ScoreModel *s)
{
    auto thresholdDiff = remainingScore - upperThresholdValue;
    if(thresholdDiff == 0) // If the remaining score is spot on 110
        return writeToScoreObject(remainingScore,trippleMaxValue,trippleDivisor,turnIndex,s);
    else if(thresholdDiff <= singleMaxValue)
        return writeToScoreObject(remainingScore,thresholdDiff,singleDivisor,turnIndex,s);
    else if(thresholdDiff <= doubleMaxValue)
    {
        if(isDivisor(thresholdDiff,doubleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,doubleDivisor,turnIndex,s);
        else if(isDivisor(thresholdDiff,trippleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,trippleDivisor,turnIndex,s);
        else
            return false;
    }
    else if(thresholdDiff <= trippleMaxValue && isDivisor(thresholdDiff,trippleDivisor))
        return writeToScoreObject(remainingScore,thresholdDiff,trippleDivisor,turnIndex,s);
    else
        return false;
}

bool PointLogisticManager::determineRouteByDiff(const int &remainingScore,const int &turnIndex,ScoreModel *scoreObject)
{
    auto diff = remainingScore - _terminalThreshold;

    if(diff <= singleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,singleMaxValue,singleDivisor,scoreObject);
    else if(remainingScore % 2 == 0 && diff < doubleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,doubleMaxValue,doubleDivisor,scoreObject);
    else if(remainingScore % 2 != 0 && diff < trippleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,trippleMaxValue,trippleDivisor,scoreObject);
    else if(diff >= trippleMaxValue)
        return writeToScoreObject(remainingScore,trippleMaxValue,trippleDivisor,turnIndex,scoreObject);
    return false;
}

bool PointLogisticManager::findLongestDivisibleWithinThreshold(const int &remainingScore,
                                                const int &turnIndex,
                                                const int &limit,
                                                const int &divisor,
                                                ScoreModel *s)
{
    auto newScore = remainingScore;
    for (int i = limit; i > 0; i -= divisor) {
        auto endScore = remainingScore - i;
        if(endScore < _terminalThreshold && endScore % _terminalDivisor == 0)
        {
            return writeToScoreObject(remainingScore,i,divisor,turnIndex,s);
        }
    }
    return false;
}

bool PointLogisticManager::writeToScoreObject(const int &score,
                                              const int &points,
                                              const int &divisor,
                                              const int &turnIndex,
                                              ScoreModel *s)
{
    auto newScore = score;
    newScore -= points;
    auto turnScore = points/divisor;
    auto identifier = identifiers[divisor - 1];
    try {
        updateScoreObject(identifier,turnScore,turnIndex,s);
        if(newScore == 0)
            return true;
        else
            return pointSuggestion(newScore,turnIndex + 1,s);
    }  catch (const char *e) {
        throw e;
    }
}
