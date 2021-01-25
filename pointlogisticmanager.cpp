#include "pointlogisticmanager.h"

bool PointLogisticManager::pointSuggestion(const int &remainingScore,
                                           const int &turnIndex,
                                           ScoreModel *scoreObject)
{
    auto totalTurns = _throwCount;
    int remainingTurns = totalTurns - turnIndex;
    /*
     * Evaluate constrains
     */
    if(!evaluateConstraints(remainingScore,turnIndex,totalTurns))
        return false;
    /*
     * The terminal state
     *
     * The algorithm checks if the remaining score is below the terminal threshold, and if that's the case,
     *  how to get to the terminal point. If not, the algorithm proceeds to find another way to reach terminal state.
     */
    if(remainingScore <= _terminalThreshold)
        return isWithinTerminalThreshold(remainingScore,turnIndex,scoreObject);
    else if(remainingTurns == 0 && remainingScore != _bullsEye)
        return false;
    /*
     * This is the pathfinding state where the algorithm tries to determine, if exists, the route.
     * If this is the last round, no ways exists, and the algorithm terminates with false.
     */
    if(remainingScore == _bullsEye)
        return writeToScoreObject(remainingScore,_bullsEye,_singleDivisor,turnIndex,scoreObject);

    if(remainingScore >= _upperThresholdValue && turnIndex == 1 && _route == 1)
        return determineRouteByThresholdDiff(remainingScore,turnIndex,scoreObject);
    else
        return determineRouteByDiff(remainingScore,turnIndex,scoreObject);
}

int PointLogisticManager::initializeLowerBound(int remainingScore, int multiplier)
{
    if(remainingScore < multiplier)
        return 0;

    auto rest = remainingScore % multiplier;

    return remainingScore - rest;
}

bool PointLogisticManager::evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns)
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
    if(remainingScore > 170 || remainingScore < _terminalDivisor)
        return false;
    else if(turnIndex < 1 || turnIndex > 3)
        return false;
    else if(totalTurns < turnIndex)
        return false;
    else
        return true;
}

PointLogisticManager::PointLogisticManager(const int &throwCount, const int &finishingKeyCode):
    _throwCount(throwCount),_lastThrowKeyCode(finishingKeyCode)
{
    _terminalThreshold = _lastThrowKeyCode == KeyMappings::SingleModifer
            ? _singleMaxValue : _lastThrowKeyCode == KeyMappings::DoubleModifier ?
                  _doubleMaxValue :
                  _trippleMaxValue;
    _terminalDivisor = _lastThrowKeyCode == KeyMappings::SingleModifer ?
                1 :_lastThrowKeyCode == KeyMappings::DoubleModifier ?
                    2 : 3;

    constructAndAddSuggestions();
}

PointLogisticManager *PointLogisticManager::createInstance(const int &numberOfThrows, const int &lastThrowKeyCode)
{
    return new PointLogisticManager(numberOfThrows,lastThrowKeyCode);
}

QString PointLogisticManager::throwSuggestion(const int &remainingScore, const int &turnIndex)
{
    if(turnIndex < 1 || turnIndex > 3)
        return QString();
    else if(remainingScore > 180)
        return QString();
    auto i = turnIndex - 1;
    auto list = _throwSuggestions.at(i);
    auto valuesAtKey = list.values(remainingScore);
    auto count = valuesAtKey.count();
    if(count == 0)
        return QString();
    auto pick = QRandomGenerator::global()->bounded(count - 1);
    auto S = valuesAtKey.at(pick);
    return S;
}

QString PointLogisticManager::constructThrowSuggestion(const int &remainingScore, const int &turnIndex, const int &route)
{
    _route = route;
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

void PointLogisticManager::setNumberOfThrows(const int &throwCount)
{
    _throwCount = throwCount;
}

void PointLogisticManager::setLastThrowKeyCode(const int &keyCode)
{
    _lastThrowKeyCode = keyCode;
}

int PointLogisticManager::lastThrowKeyCode()
{
    return _lastThrowKeyCode;
}

void PointLogisticManager::constructAndAddSuggestions()
{
    for (int turnIndex = 1; turnIndex <= _throwCount; ++turnIndex) {
        auto remainingTurns = _throwCount - turnIndex;
        auto currentPointLimit = remainingTurns*_trippleMaxValue + _bullsEye;

        auto suggestions = QMultiHash<int,QString>();
        for (int i = _trippleDivisor; i <= currentPointLimit; ++i) {
            auto firstSuggestion = constructThrowSuggestion(i,turnIndex,1);
            if(firstSuggestion != QString())
                suggestions.insert(i,firstSuggestion);
            auto secondSuggestion = constructThrowSuggestion(i,turnIndex,2);
            if(firstSuggestion != QString())
                suggestions.insert(i,secondSuggestion);
        }

        _throwSuggestions.append(suggestions);
    }
}

QString PointLogisticManager::toString(ScoreModel *s)
{
    QString result;
    for (int i = 0; i < _throwCount; ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
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
        for (int i = _singleMaxValue; i > 0; --i) {
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

bool PointLogisticManager::determineRouteByThresholdDiff(const int &remainingScore,
                                                         const int &turnIndex,ScoreModel *s)
{
    auto thresholdDiff = remainingScore - _upperThresholdValue;
    if(thresholdDiff == 0) // If the remaining score is spot on 110
        return writeToScoreObject(remainingScore,_trippleMaxValue,_trippleDivisor,turnIndex,s);
    else if(thresholdDiff == _bullsEye || thresholdDiff == _bull) // Bullseye
        return writeToScoreObject(remainingScore,thresholdDiff,_singleDivisor,turnIndex,s);
    else if(thresholdDiff <= _singleMaxValue)
        return writeToScoreObject(remainingScore,thresholdDiff,_singleDivisor,turnIndex,s);
    else if(thresholdDiff <= _doubleMaxValue)
    {
        if(isDivisor(thresholdDiff,_doubleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,_doubleDivisor,turnIndex,s);
        else if(isDivisor(thresholdDiff,_trippleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,_trippleDivisor,turnIndex,s);
        else
            return false;
    }
    else if(thresholdDiff <= _trippleMaxValue && isDivisor(thresholdDiff,_trippleDivisor))
        return writeToScoreObject(remainingScore,thresholdDiff,_trippleDivisor,turnIndex,s);
    else
        return false;
}

bool PointLogisticManager::determineRouteByDiff(const int &remainingScore,const int &turnIndex,ScoreModel *scoreObject)
{
    auto diff = remainingScore - _terminalThreshold;

    if(diff <= _singleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,_singleMaxValue,_singleDivisor,scoreObject);
    else if(remainingScore % 2 == 0 && diff < _doubleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,_doubleMaxValue,_doubleDivisor,scoreObject);
    else if(remainingScore % 2 != 0 && diff < _trippleMaxValue)
        return findLongestDivisibleWithinThreshold(remainingScore,turnIndex,_trippleMaxValue,_trippleDivisor,scoreObject);
    else if(diff >= _trippleMaxValue)
        return writeToScoreObject(remainingScore,_trippleMaxValue,_trippleDivisor,turnIndex,scoreObject);
    return false;
}

bool PointLogisticManager::findLongestDivisibleWithinThreshold(const int &remainingScore,
                                                const int &turnIndex,
                                                const int &limit,
                                                const int &divisor,
                                                ScoreModel *s)
{
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

bool PointLogisticManager::isDivisor(int base, int div)
{
    if(base == 0 || div == 0)
        throw new std::domain_error("One of operands zero");

    return base % div == 0;
}

void PointLogisticManager::updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s)
{
    if(value < 0)
        throw new std::out_of_range("Value out of bounds");

    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
}
