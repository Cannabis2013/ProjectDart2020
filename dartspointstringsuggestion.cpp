#include "dartspointstringsuggestion.h"

DartsPointStringSuggestion::DartsPointStringSuggestion(const int &attempts, const int &lastAttemptKeyCode):
    _attempts(attempts),_lastAttemptKeyCode(lastAttemptKeyCode)
{
    if(_lastAttemptKeyCode == KeyMappings::SingleModifer)
        _terminalThreshold = _singleMaxValue;
    else if(_lastAttemptKeyCode == KeyMappings::DoubleModifier)
        _terminalThreshold = _doubleMaxValue;
    else if(_lastAttemptKeyCode == KeyMappings::TrippleModifier)
        _terminalThreshold = _trippleMaxValue;

    if(_lastAttemptKeyCode == KeyMappings::SingleModifer)
        _terminalDivisor = 1;
    else if(_lastAttemptKeyCode == KeyMappings::DoubleModifier)
        _terminalDivisor = 2;
    else if(_lastAttemptKeyCode == KeyMappings::TrippleModifier)
        _terminalDivisor = 3;

    constructAndAddSuggestions();
}

void DartsPointStringSuggestion::constructAndAddSuggestions()
{
    for (int turnIndex = 1; turnIndex <= attempts(); ++turnIndex) {
        auto remainingTurns = attempts() - turnIndex;
        auto currentPointLimit = remainingTurns*_trippleMaxValue + _bullsEye;

        auto suggestions = QMultiHash<int,QString>();
        for (int i = _doubleDivisor; i <= currentPointLimit; ++i) {
            auto firstSuggestion = constructThrowSuggestion(i,turnIndex);
            if(firstSuggestion != QString())
                suggestions.insert(i,firstSuggestion);
        }

        _throwSuggestions.append(suggestions);
    }
}

QString DartsPointStringSuggestion::constructThrowSuggestion(const int &remainingScore,
                                                          const int &turnIndex)
{
    auto score = new PointLogisticContext::ScoreModel();

    score->multiplier = QVector<char>(_attempts,'\0');
    score->pointValue = QVector<int>(_attempts,0);

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

bool DartsPointStringSuggestion::pointSuggestion(const int &remainingScore,
                                              const int &turnIndex,
                                              PointLogisticContext::ScoreModel *scoreObject)
{
    auto totalTurns = attempts();
    /*
     * Evaluate constrains
     */
    if(!evaluateConstraints(remainingScore,turnIndex,totalTurns))
        return false;
    /*
     * The terminal state
     *
     * The algorithm checks if the remaining score is below the terminal threshold, and if that's the case,
     *  how to get to terminal point. If not, the algorithm proceeds to find another way.
     */
    if(remainingScore <= _terminalThreshold)
        return isWithinTerminalThreshold(remainingScore,turnIndex,scoreObject);
    else if(turnIndex == attempts() && remainingScore != _bullsEye)
        return false;
    /*
     * This is the pathfinding state where the algorithm tries to determine, if exists, the route.
     * If this is the last round, no ways exists, and the algorithm terminates with false.
     */
    if(remainingScore == _bullsEye)
        return writeToScoreObject(remainingScore,_bullsEye,_singleDivisor,turnIndex,scoreObject);

    if(remainingScore >= upperThresholdValue() && turnIndex == 1)
        return determineRouteByThresholdDiff(remainingScore,turnIndex,scoreObject);
    else
        return determineRouteByDiff(remainingScore,turnIndex,scoreObject);

}

bool DartsPointStringSuggestion::evaluateConstraints(const int &remainingScore,
                                                  const int &turnIndex,
                                                  const int &totalTurns)
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

bool DartsPointStringSuggestion::isWithinTerminalThreshold(const int &remainingScore,
                                                        const int &turnIndex,
                                                        PointLogisticContext::ScoreModel *scoreObject)
{
    auto newScore = remainingScore;
    if(isDivisor(remainingScore,_terminalDivisor))
    {
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

bool DartsPointStringSuggestion::isDivisor(int base, int div)
{
    if(base == 0 || div == 0)
        throw new std::domain_error("One of operands zero");

    return base % div == 0;
}

bool DartsPointStringSuggestion::
determineRouteByThresholdDiff(const int &remainingScore,
                                                            const int &turnIndex,
                                                            PointLogisticContext::ScoreModel *s)
{
    auto thresholdDiff = remainingScore - _upperThresholdValue;
    if(thresholdDiff == 0) // If the remaining score is spot on 110
        return writeToScoreObject(remainingScore,_trippleMaxValue,_trippleDivisor,turnIndex,s);
    else if(thresholdDiff == bullsEye() || thresholdDiff == _bull) // Bullseye
        return writeToScoreObject(remainingScore,thresholdDiff,_singleDivisor,turnIndex,s);
    else if(thresholdDiff <= _singleMaxValue)
        return writeToScoreObject(remainingScore,thresholdDiff,_singleDivisor,turnIndex,s);
    else if(thresholdDiff <= doubleMaxValue())
    {
        if(isDivisor(thresholdDiff,_doubleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,_doubleDivisor,turnIndex,s);
        else if(isDivisor(thresholdDiff,_trippleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,_trippleDivisor,turnIndex,s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
    }
    else if(thresholdDiff <= trippleMaxValue())
    {
        if(isDivisor(thresholdDiff,_trippleDivisor))
            return writeToScoreObject(remainingScore,thresholdDiff,_trippleDivisor,turnIndex,s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
        else if(isEven(thresholdDiff))
            return writeToScoreObject(remainingScore,trippleMaxValue(),trippleDivisor(),turnIndex,s);
    }
    return false;
}

bool DartsPointStringSuggestion::determineRouteByDiff(const int &remainingScore,
                                                   const int &turnIndex,
                                                   PointLogisticContext::ScoreModel *scoreObject)
{
    auto diff = remainingScore - _terminalThreshold;

    if(diff <= _singleMaxValue)
        return findGreatestPointsWithinThreshold(remainingScore,turnIndex,_singleMaxValue,_singleDivisor,scoreObject);
    else if(diff < _trippleMaxValue)
        return findGreatestPointsWithinTerminalThreshold(remainingScore,turnIndex,_trippleMaxValue,scoreObject);
    else if(diff >= _trippleMaxValue)
        return writeToScoreObject(remainingScore,_trippleMaxValue,_trippleDivisor,turnIndex,scoreObject);
    return false;
}

bool DartsPointStringSuggestion::findGreatestPointsWithinThreshold(const int &remainingScore,
                                                                           const int &turnIndex,
                                                                           const int &threshold,
                                                                           const int &divisor,
                                                                           PointLogisticContext::ScoreModel *s)
{
    for (int points = threshold; points > 0; points -= divisor) {
        auto endScore = remainingScore - points;
        if(endScore <= terminalThreshold() && endScore % terminalDivisor() == 0)
            return writeToScoreObject(remainingScore,points,divisor,turnIndex,s);
        else if(endScore >= _terminalThreshold)
            return false;
    }
    return false;
}

bool DartsPointStringSuggestion::findGreatestPointsWithinTerminalThreshold(const int &remainingScore,
                                                              const int &turnIndex,
                                                              const int &threshold,
                                                              PointLogisticContext::ScoreModel *s)
{
    for (int points = threshold; points > 0; points--) {
        auto endScore = remainingScore - points;
        if(endScore < _terminalThreshold && endScore >= terminalDivisor())
        {
            if(points % _terminalDivisor == 0 && points <= doubleMaxValue())
                return writeToScoreObject(remainingScore,points,doubleDivisor(),turnIndex,s);
            else if(points % trippleDivisor() == 0 && points <= trippleMaxValue())
                return writeToScoreObject(remainingScore,points,trippleDivisor(),turnIndex,s);
        }
    }
    return false;
}

bool DartsPointStringSuggestion::findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex, PointLogisticContext::ScoreModel *s)
{
    for (int points = trippleMaxValue(); points > 0; points -= trippleDivisor()) {
        auto endScore = remainingScore - points;
        if(isEven(endScore) && endScore <= upperThresholdValue())
            return writeToScoreObject(remainingScore,points,trippleDivisor(),turnIndex,s);
    }
    return false;
}

void DartsPointStringSuggestion::updateScoreObject(char stringIdentifier, int value, int index, PointLogisticContext::ScoreModel *s)
{
    if(value < 0)
        throw new std::out_of_range("Value out of bounds");

    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
}

bool DartsPointStringSuggestion::writeToScoreObject(const int &remainingScore,
                                                 const int &points,
                                                 const int &divisor,
                                                 const int &turnIndex, PointLogisticContext::ScoreModel *s)
{
    auto newScore = remainingScore - points;
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

QString DartsPointStringSuggestion::toString(PointLogisticContext::ScoreModel *s)
{
    QString result;
    for (int i = 0; i < attempts(); ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
    }

    return result;
}

int DartsPointStringSuggestion::terminalThreshold() const
{
    return _terminalThreshold;
}

int DartsPointStringSuggestion::terminalDivisor() const
{
    return _terminalDivisor;
}

int DartsPointStringSuggestion::singleDivisor() const
{
    return _singleDivisor;
}

int DartsPointStringSuggestion::doubleDivisor() const
{
    return _doubleDivisor;
}

int DartsPointStringSuggestion::trippleDivisor() const
{
    return _trippleDivisor;
}

int DartsPointStringSuggestion::upperThresholdValue() const
{
    return _upperThresholdValue;
}

int DartsPointStringSuggestion::bull() const
{
    return _bull;
}

int DartsPointStringSuggestion::bullsEye() const
{
    return _bullsEye;
}

int DartsPointStringSuggestion::singleMaxValue() const
{
    return _singleMaxValue;
}

int DartsPointStringSuggestion::doubleMaxValue() const
{
    return _doubleMaxValue;
}

int DartsPointStringSuggestion::trippleMaxValue() const
{
    return _trippleMaxValue;
}

int DartsPointStringSuggestion::attempts() const
{
    return _attempts;
}

DartsPointStringSuggestion *DartsPointStringSuggestion::createInstance(const int &attemps, const int &lastAttemptKeyCode)
{
    return new DartsPointStringSuggestion(attemps,lastAttemptKeyCode);
}

QString DartsPointStringSuggestion::suggestTargetRow(const int &remainingScore, const int &turnIndex) const
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
    //auto pick = QRandomGenerator::global()->bounded(count - 1);
    auto S = valuesAtKey.at(0);
    return S;
}

bool DartsPointStringSuggestion::isEven(const int &integer)
{
    auto result = integer % 2 == 0;
    return result;
}

int DartsPointStringSuggestion::lastAttemptKeyCode()
{
    return _lastAttemptKeyCode;
}
