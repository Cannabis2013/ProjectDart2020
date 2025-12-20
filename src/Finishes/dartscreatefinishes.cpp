#include "dartscreatefinishes.h"

DartsCreateFinishes::TargetRows *DartsCreateFinishes::constructRows()
{
    TargetRows *allTargetRows = new TargetRows();
    for (int turnIndex = 1; turnIndex <= _attempts; ++turnIndex) {
        auto remainingTurns = _attempts - turnIndex;
        auto currentPointLimit = remainingTurns * _values->trippleMaxValue() + 50;
        auto suggestions = new TargetRow;
        for (int i = _values->doubleDivisor(); i <= currentPointLimit; ++i) {
            auto firstSuggestion = constructRow(i, turnIndex);
            if (firstSuggestion != QString())
                suggestions->insert(i, firstSuggestion);
        }
        allTargetRows->append(suggestions);
    }
    return allTargetRows;
}

QString DartsCreateFinishes::constructRow(const int &remainingScore, const int &turnIndex) const
{
    auto score = new ScoreModel;
    score->multiplier = QVector<char>(_attempts, '\0');
    score->pointValue = QVector<int>(_attempts, 0);
    return suggestion(remainingScore, turnIndex, score) ? toString(score) : QString();
}

bool DartsCreateFinishes::suggestion(const int &remainingScore, const int &turnIndex,
                                         ScoreModel *scoreObject) const
{
    /*
     * Evaluate constrains
     */
    if (!evaluateConstraints(remainingScore, turnIndex, _attempts))
        return false;
    /*
     * The terminal state
     *
     * The algorithm checks if the remaining score is below the terminal threshold, and if that's the case,
     *  how to get to terminal point. If not, the algorithm proceeds to find another way.
     */
    if (remainingScore <= _values->terminalThreshold())
        return isWithinTerminalThreshold(remainingScore, turnIndex, scoreObject);
    else if (turnIndex == _attempts && remainingScore != 50)
        return false;
    /*
     * This is the pathfinding state where the algorithm tries to determine, if exists, the route.
     * If this is the last round, no ways exist, and the algorithm terminates with false.
     */
    if (remainingScore == 50)
        return writeToScoreObject(remainingScore, 50, 1, turnIndex, scoreObject);
    if (remainingScore >= 110 && turnIndex == 1)
        return determineRouteByThresholdDiff(remainingScore, turnIndex, scoreObject);
    else
        return determineRouteByDiff(remainingScore, turnIndex, scoreObject);
}

bool DartsCreateFinishes::evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns) const
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
    if (remainingScore > 170 || remainingScore < _terminalDivisor)
        return false;
    else if (turnIndex < 1 || turnIndex > 3)
        return false;
    else if (totalTurns < turnIndex)
        return false;
    else
        return true;
}

bool DartsCreateFinishes::isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   ScoreModel *scoreObject) const
{
    auto newScore = remainingScore;
    if (isDivisor(remainingScore, _terminalDivisor)) {
        auto turnScore = remainingScore / _terminalDivisor;
        auto identifier = _values->identifierByDivisor(_terminalDivisor);
        return updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
    } else {
        for (int i = _values->singleMaxValue(); i > 0; --i) {
            auto endScore = remainingScore - i;
            if (endScore < _values->terminalThreshold()
                && endScore > 0
                && endScore % _terminalDivisor == 0) {
                newScore -= i;
                return updateScoreObject('S', i, turnIndex, scoreObject)
                         ? suggestion(newScore, turnIndex + 1, scoreObject)
                         : false;
            }
        }
    }
    return false;
}

bool DartsCreateFinishes::isDivisor(int base, int div) const
{
    if(base == 0 || div == 0)
        throw new std::domain_error("One of operands zero");
    return base % div == 0;
}

bool DartsCreateFinishes::determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex, ScoreModel *s) const
{
    auto thresholdDiff = remainingScore - _values->upperThresholdValue();
    if(thresholdDiff == 0) // If the remaining score is spot on 110
        return writeToScoreObject(remainingScore,
                                  _values->trippleMaxValue(),
                                  _values->trippleDivisor(),
                                  turnIndex,
                                  s);
    else if (thresholdDiff == 50 || thresholdDiff == _values->bull()) // Bullseye
        return writeToScoreObject(remainingScore,
                                  thresholdDiff,
                                  _values->singleDivisor(),
                                  turnIndex,
                                  s);
    else if (thresholdDiff <= _values->singleMaxValue())
        return writeToScoreObject(remainingScore,
                                  thresholdDiff,
                                  _values->singleDivisor(),
                                  turnIndex,
                                  s);
    else if (thresholdDiff <= _values->doubleMaxValue()) {
        if (isDivisor(thresholdDiff, _values->doubleDivisor()))
            return writeToScoreObject(remainingScore,
                                      thresholdDiff,
                                      _values->doubleDivisor(),
                                      turnIndex,
                                      s);
        else if (isDivisor(thresholdDiff, _values->trippleDivisor()))
            return writeToScoreObject(remainingScore,
                                      thresholdDiff,
                                      _values->trippleDivisor(),
                                      turnIndex,
                                      s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
    } else if (thresholdDiff <= _values->trippleMaxValue()) {
        if (isDivisor(thresholdDiff, _values->trippleDivisor()))
            return writeToScoreObject(remainingScore,
                                      thresholdDiff,
                                      _values->trippleDivisor(),
                                      turnIndex,
                                      s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
        else if(isEven(thresholdDiff))
            return writeToScoreObject(remainingScore,
                                      _values->trippleMaxValue(),
                                      _values->trippleDivisor(),
                                      turnIndex,
                                      s);
    }
    return false;
}

bool DartsCreateFinishes::determineRouteByDiff(const int &remainingScore, const int &turnIndex,
                                              ScoreModel *scoreObject) const
{
    auto diff = remainingScore - _values->terminalThreshold();

    if (diff <= _values->singleMaxValue())
        return findGreatestPointsWithinThreshold(remainingScore,
                                                 turnIndex,
                                                 _values->singleMaxValue(),
                                                 _values->singleDivisor(),
                                                 scoreObject);
    else if (diff < _values->trippleMaxValue())
        return findGreatestPointsWithinTerminalThreshold(remainingScore,
                                                         turnIndex,
                                                         _values->trippleMaxValue(),
                                                         scoreObject);
    else if (diff >= _values->trippleMaxValue())
        return writeToScoreObject(remainingScore,
                                  _values->trippleMaxValue(),
                                  _values->trippleDivisor(),
                                  turnIndex,
                                  scoreObject);
    return false;
}

bool DartsCreateFinishes::findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                                            const int &threshold, const int &divisor,
                                                            ScoreModel *s) const
{
    for (int points = threshold; points > 0; points -= divisor) {
        auto endScore = remainingScore - points;
        if (endScore <= _values->terminalThreshold() && endScore % _terminalDivisor == 0)
            return writeToScoreObject(remainingScore,points,divisor,turnIndex,s);
        else if (endScore >= _values->terminalThreshold())
            return false;
    }
    return false;
}

bool DartsCreateFinishes::findGreatestPointsWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                                   const int &threshold,
                                                                   ScoreModel *s) const
{
    for (int points = threshold; points > 0; points--) {
        auto endScore = remainingScore - points;
        if (endScore < _values->terminalThreshold() && endScore >= _terminalDivisor) {
            if (points % _terminalDivisor == 0 && points <= _values->doubleMaxValue())
                return writeToScoreObject(remainingScore,
                                          points,
                                          _values->doubleDivisor(),
                                          turnIndex,
                                          s);
            else if (points % _values->trippleDivisor() == 0 && points <= _values->trippleMaxValue())
                return writeToScoreObject(remainingScore,
                                          points,
                                          _values->trippleDivisor(),
                                          turnIndex,
                                          s);
        }
    }
    return false;
}

bool DartsCreateFinishes::findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex,ScoreModel *s) const
{
    for (int points = _values->trippleMaxValue(); points > 0; points -= _values->trippleDivisor()) {
        auto endScore = remainingScore - points;
        if (isEven(endScore) && endScore <= _values->upperThresholdValue())
            return writeToScoreObject(remainingScore,
                                      points,
                                      _values->trippleDivisor(),
                                      turnIndex,
                                      s);
    }
    return false;
}

bool DartsCreateFinishes::updateScoreObject(char stringIdentifier,
                                            int value,
                                            int index,
                                            ScoreModel *s) const
{
    if(value < 0)
        return false;
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
    return true;
}

bool DartsCreateFinishes::writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                                            const int &turnIndex, ScoreModel *s) const
{
    auto newScore = remainingScore - points;
    auto turnScore = points/divisor;
    auto identifier = _values->identifierByDivisor(divisor);
    try {
        updateScoreObject(identifier,turnScore,turnIndex,s);
        if(newScore == 0)
            return true;
        else
            return suggestion(newScore,turnIndex + 1,s);
    }  catch (const char *e) {
        throw e;
    }
}

bool DartsCreateFinishes::isEven(const int &integer) const
{
    return integer % 2 == 0;
}

QString DartsCreateFinishes::toString(ScoreModel *s) const
{
    QString result;
    for (int i = 0; i < _attempts; ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
    }
    return result;
}
