#include "finishconstructor.h"

#ifdef USE_IMP1

FinishConstructor::TargetRows *FinishConstructor::construct()
{
    TargetRows *allTargetRows = new TargetRows();
    for (int turnIndex = 1; turnIndex <= ATTEMPTS; ++turnIndex) {
        auto remainingTurns = ATTEMPTS - turnIndex;
        auto currentPointLimit = remainingTurns * TRIPPLE_MAX + BULLS;
        auto suggestions = new Finish;
        for (int i = DOUBLE_MAX; i <= currentPointLimit; ++i) {
            auto firstSuggestion = constructRow(i, turnIndex);
            if (firstSuggestion != QString())
                suggestions->insert(i, firstSuggestion);
        }
        allTargetRows->append(suggestions);
    }
    return allTargetRows;
}

char FinishConstructor::multiplierToString(const int &divisor) const
{
    if (divisor >= 1 && divisor <= 3)
        return identifiers[divisor - 1];
    throw "Divisor not valid";
}

QString FinishConstructor::constructRow(const int &remainingScore, const int &turnIndex) const
{
    auto score = new ScoreModel;
    score->multiplier = QVector<char>(ATTEMPTS, '\0');
    score->pointValue = QVector<int>(ATTEMPTS, 0);
    return suggestion(remainingScore, turnIndex, score) ? toString(score) : QString();
}

bool FinishConstructor::suggestion(const int &remainingScore,
                                   const int &turnIndex,
                                   ScoreModel *scoreObject) const
{
    if (remainingScore > 170 || remainingScore < DOUBLE_MULTIPLIER)
        return false;
    else if (turnIndex < 1 || turnIndex > 3)
        return false;
    else if (turnIndex >= ATTEMPTS)
        return false;

    if (remainingScore <= DOUBLE_MAX)
        return isWithinTerminalThreshold(remainingScore, turnIndex, scoreObject);
    else if (turnIndex == ATTEMPTS && remainingScore != BULLS)
        return false;
    if (remainingScore == BULLS)
        return updateScoreObject('S', BULLS, turnIndex, scoreObject);
    if (remainingScore >= UPPER_LIMIT && turnIndex == 1)
        return determineRouteByDiff(remainingScore, turnIndex, scoreObject);
    else
        return determineRouteByDiff(remainingScore, turnIndex, scoreObject);
}

bool FinishConstructor::isWithinTerminalThreshold(const int &remainingScore,
                                                  const int &turnIndex,
                                                  ScoreModel *scoreObject) const
{
    auto newScore = remainingScore;
    if (remainingScore % DOUBLE_MULTIPLIER == 0) {
        auto turnScore = remainingScore / DOUBLE_MULTIPLIER;
        auto identifier = multiplierToString(DOUBLE_MULTIPLIER);
        return updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
    } else {
        for (int i = SINGLE_MAX; i > 0; --i) {
            auto endScore = remainingScore - i;
            if (endScore < DOUBLE_MAX && endScore > 0 && endScore % DOUBLE_MULTIPLIER == 0) {
                newScore -= i;
                return updateScoreObject('S', i, turnIndex, scoreObject)
                         ? suggestion(newScore, turnIndex + 1, scoreObject)
                         : false;
            }
        }
    }
    return false;
}

bool FinishConstructor::determineRouteByDiff(const int &remainingScore,
                                             const int &turnIndex,
                                             ScoreModel *scoreObject) const
{
    auto diff = remainingScore - DOUBLE_MAX;

    if (diff <= SINGLE_MAX)
        return findGreatestPointsWithinThreshold(remainingScore,
                                                 turnIndex,
                                                 SINGLE_MAX,
                                                 SINGLE_MULTIPLIER,
                                                 scoreObject);
    else if (diff < TRIPPLE_MAX)
        return findGreatestPointsWithinTerminalThreshold(remainingScore,
                                                         turnIndex,
                                                         TRIPPLE_MAX,
                                                         scoreObject);
    else if (diff >= TRIPPLE_MAX)
        return writeToScoreObject(remainingScore,
                                  TRIPPLE_MAX,
                                  TRIPPLE_MULTIPLIER,
                                  turnIndex,
                                  scoreObject);
    return false;
}

bool FinishConstructor::findGreatestPointsWithinThreshold(const int &remainingScore,
                                                          const int &turnIndex,
                                                          const int &threshold,
                                                          const int &divisor,
                                                          ScoreModel *s) const
{
    for (int points = threshold; points > 0; points -= divisor) {
        auto endScore = remainingScore - points;
        if (endScore <= DOUBLE_MAX && endScore % DOUBLE_MULTIPLIER == 0)
            return writeToScoreObject(remainingScore, points, divisor, turnIndex, s);
        else if (endScore >= DOUBLE_MAX)
            return false;
    }
    return false;
}

bool FinishConstructor::findGreatestPointsWithinTerminalThreshold(const int &remainingScore,
                                                                  const int &turnIndex,
                                                                  const int &threshold,
                                                                  ScoreModel *s) const
{
    for (int points = threshold; points > 0; points--) {
        auto endScore = remainingScore - points;
        if (endScore < DOUBLE_MAX && endScore >= DOUBLE_MULTIPLIER) {
            if (points % DOUBLE_MULTIPLIER == 0 && points <= DOUBLE_MAX)
                return writeToScoreObject(remainingScore, points, DOUBLE_MAX, turnIndex, s);
            else if (points % TRIPPLE_MULTIPLIER == 0 && points <= TRIPPLE_MAX)
                return writeToScoreObject(remainingScore, points, TRIPPLE_MULTIPLIER, turnIndex, s);
        }
    }
    return false;
}

bool FinishConstructor::findGreatestOddDivisibleByThree(const int &remainingScore,
                                                        const int &turnIndex,
                                                        ScoreModel *s) const
{
    for (int points = TRIPPLE_MAX; points > 0; points -= TRIPPLE_MULTIPLIER) {
        auto endScore = remainingScore - points;
        if (endScore % 2 == 0 && endScore <= UPPER_LIMIT)
            return writeToScoreObject(remainingScore, points, TRIPPLE_MULTIPLIER, turnIndex, s);
    }
    return false;
}

bool FinishConstructor::updateScoreObject(char stringIdentifier,
                                          int value,
                                          int index,
                                          ScoreModel *s) const
{
    if (value < 0)
        return false;
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
    return true;
}

bool FinishConstructor::writeToScoreObject(const int &remainingScore,
                                           const int &points,
                                           const int &divisor,
                                           const int &turnIndex,
                                           ScoreModel *s) const
{
    auto newScore = remainingScore - points;
    if (newScore == 0 && points != BULLS)
        return true;

    auto turnScore = points / divisor;
    auto identifier = multiplierToString(divisor);
    auto result = updateScoreObject(identifier, turnScore, turnIndex, s);
    return result ? suggestion(newScore, turnIndex + 1, s) : false;
}

QString FinishConstructor::toString(ScoreModel *s) const
{
    QString result;
    for (int i = 0; i < ATTEMPTS; ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
    }
    return result;
}
#endif
