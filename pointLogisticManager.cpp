#include "pointlogisticmanager.h"

bool PointLogisticManager::pointSuggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject)
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
    int remainingTurns = totalTurns - turnIndex;

    if(remainingScore > 170 || remainingScore <= 0)
        return false;
    else if(turnIndex < 1 || turnIndex > 3)
        return false;
    else if(totalTurns < turnIndex)
        return false;


    /*
         * The terminal state
         *
         * Here it will be determined whether the score is in the reach of terminal state or not.
         *
         * If not, the algorithm tries to find another ways to reach terminal state.
         */
    if(remainingScore <= _terminalThreshold)
        return isWithinTerminalThreshold(remainingScore,turnIndex,scoreObject);
    else if(remainingTurns == 0 && remainingScore != BullsEye)
        return false;
    /*
     * This is the pathfinding state where the algorithm tries to determine wheter possible routes exists.
     * If this is the last round, no ways exists, and the algorithm terminates with false.
     */

    if(remainingScore == BullsEye)
    {
        try {
            updateScoreObject('S',BullsEye,turnIndex,scoreObject);
            return true;
        } catch (std::out_of_range *e) {
            throw e;
        }
    }

    if(remainingScore >= upperThresholdValue && turnIndex == 1)
        return isWithinUpperThreshold(remainingScore,turnIndex,scoreObject);

    return isDiffWithinReach(remainingScore,turnIndex,scoreObject);
}

QString PointLogisticManager::constructThrowSuggestions(const int &remainingScore, const int &turnIndex)
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

bool PointLogisticManager::isWithinUpperThreshold(const int &remainingScore, const int &turnIndex,ScoreModel *s)
{
    auto newScore = remainingScore;

    auto thresholdDiff = remainingScore - upperThresholdValue;
    if(thresholdDiff <= singleMaxValue)
    {
        newScore -= thresholdDiff;
        try {
            updateScoreObject('S',thresholdDiff,turnIndex,s);
            return pointSuggestion(newScore,turnIndex + 1,s);
        }  catch (const char *e) {
            throw e;
        }
    }
    if(thresholdDiff <= doubleMaxValue)
    {
        if(isDivisor(thresholdDiff,doubleDivisor))
        {
            newScore -= thresholdDiff;
            auto turnScore = thresholdDiff / doubleDivisor;
            try {
                updateScoreObject('D',turnScore,turnIndex,s);
                return pointSuggestion(newScore,turnIndex + 1,s);
            }  catch (const char *e) {
                throw e;
            }
        }
        else if(isDivisor(thresholdDiff,trippleDivisor))
        {
            newScore -= thresholdDiff;
            auto turnScore = thresholdDiff / trippleDivisor;
            try {
                updateScoreObject('T',turnScore,turnIndex,s);
                return pointSuggestion(newScore,turnIndex + 1,s);
            }  catch (const char *e) {
                throw e;
            }
        }
        else
            return false;
    }
    else if(thresholdDiff <= trippleMaxValue && isDivisor(thresholdDiff,trippleDivisor))
    {
        newScore -= thresholdDiff;
        auto turnScore = thresholdDiff / trippleDivisor;
        try {
            updateScoreObject('T',turnScore,turnIndex,s);
            return pointSuggestion(newScore,turnIndex + 1,s);
        }  catch (const char *e) {
            throw e;
        }
    }
    else
        return false;
}

bool PointLogisticManager::isDiffWithinReach(const int &remainingScore,const int &turnIndex,ScoreModel *scoreObject)
{
    auto diff = remainingScore - _terminalThreshold;
    auto newScore = remainingScore;

    if(diff <= singleMaxValue)
    {
        for (int i = singleMaxValue; i > 0; --i) {
            auto endScore = remainingScore - i;
            if(endScore < _terminalThreshold && endScore % _terminalDivisor == 0)
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
    else if(remainingScore % 2 == 0 && diff < doubleMaxValue)
    {
        for (int i = doubleMaxValue; i > 0; i -= 2) {
            auto endScore = remainingScore - i;
            if(endScore < _terminalThreshold && endScore % _terminalDivisor)
            {
                newScore -= i;
                auto turnScore = i/2;
                try {
                    updateScoreObject('D',turnScore,turnIndex,scoreObject);
                    return pointSuggestion(newScore,turnIndex,scoreObject);
                }  catch (const char *e) {
                    throw e;
                }
            }
        }
    }
    else if(remainingScore % 2 != 0 && diff < trippleMaxValue)
    {
        for (int i = trippleMaxValue; i > 0; i -= 3) {
            auto endScore = remainingScore - i;
            if(endScore < _terminalThreshold && endScore % _terminalDivisor && endScore > 0)
            {
                newScore -= i;
                auto turnScore = i/3;
                try {
                    updateScoreObject('T',turnScore,turnIndex,scoreObject);
                    return pointSuggestion(newScore,turnIndex + 1,scoreObject);
                }  catch (const char *e) {
                    throw e;
                }
            }
        }
    }
    else if(diff >= trippleMaxValue)
    {
        newScore -= trippleMaxValue;
        auto turnScore = trippleMaxValue/3;
        try {
            updateScoreObject('T',turnScore,turnIndex,scoreObject);
            return pointSuggestion(newScore,turnIndex + 1,scoreObject);
        }  catch(const char *e) {
            throw e;
        }
    }
    return false;
}
