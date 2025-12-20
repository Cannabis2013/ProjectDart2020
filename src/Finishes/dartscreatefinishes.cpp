#include "dartscreatefinishes.h"

#define TRIPPLE_MAX 60
#define DOUBLE_MAX 40
#define SINGLE_MAX 20
#define SINGLE_DIVISOR 1
#define DOUBLE_DIVISOR 2
#define TRIPPLE_DIVISOR 3
#define ATTEMPTS 3
#define TERMINAL_DIVISOR 2
#define TERMINAL_LIMIT 40
#define BULL 25
#define BULLS 50
#define UPPER_LIMIT 110

DartsCreateFinishes::TargetRows *DartsCreateFinishes::constructRows()
{
    TargetRows *allTargetRows = new TargetRows();
    for (int turnIndex = 1; turnIndex <= ATTEMPTS; ++turnIndex) {
        auto remainingTurns = ATTEMPTS - turnIndex;
        auto currentPointLimit = remainingTurns * TRIPPLE_MAX + 50;
        auto suggestions = new TargetRow;
        for (int i = DOUBLE_DIVISOR; i <= currentPointLimit; ++i) {
            auto firstSuggestion = constructRow(i, turnIndex);
            if (firstSuggestion != QString())
                suggestions->insert(i, firstSuggestion);
        }
        allTargetRows->append(suggestions);
    }
    return allTargetRows;
}

char DartsCreateFinishes::identifierByDivisor(const int &divisor) const
{
    if (divisor >= 1 && divisor <= 3)
        return identifiers[divisor - 1];
    throw "Divisor not valid";
}

QString DartsCreateFinishes::constructRow(const int &remainingScore, const int &turnIndex) const
{
    auto score = new ScoreModel;
    score->multiplier = QVector<char>(ATTEMPTS, '\0');
    score->pointValue = QVector<int>(ATTEMPTS, 0);
    return suggestion(remainingScore, turnIndex, score) ? toString(score) : QString();
}

bool DartsCreateFinishes::suggestion(const int &remainingScore, const int &turnIndex,ScoreModel *scoreObject) const
{
    if (!evaluateConstraints(remainingScore, turnIndex, ATTEMPTS))
        return false;
    if (remainingScore <= TERMINAL_LIMIT)
        return isWithinTerminalThreshold(remainingScore, turnIndex, scoreObject);
    else if (turnIndex == ATTEMPTS && remainingScore != BULLS)
        return false;
    if (remainingScore == BULLS)
        return writeToScoreObject(remainingScore, BULLS, 1, turnIndex, scoreObject);
    if (remainingScore >= UPPER_LIMIT && turnIndex == 1)
        return determineRouteByDiff(remainingScore, turnIndex, scoreObject);
    else
        return determineRouteByDiff(remainingScore, turnIndex, scoreObject);
}

bool DartsCreateFinishes::evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns) const
{
    if (remainingScore > 170 || remainingScore < TERMINAL_DIVISOR)
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
    if (isDivisor(remainingScore, TERMINAL_DIVISOR)) {
        auto turnScore = remainingScore / TERMINAL_DIVISOR;
        auto identifier = identifierByDivisor(TERMINAL_DIVISOR);
        return updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
    } else {
        for (int i = SINGLE_MAX; i > 0; --i) {
            auto endScore = remainingScore - i;
            if (endScore < TERMINAL_LIMIT && endScore > 0 && endScore % TERMINAL_DIVISOR == 0) {
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

bool DartsCreateFinishes::determineRouteByDiff(const int &remainingScore,
                                               const int &turnIndex,
                                               ScoreModel *scoreObject) const
{
    auto diff = remainingScore - TERMINAL_LIMIT;

    if (diff <= SINGLE_MAX)
        return findGreatestPointsWithinThreshold(remainingScore,turnIndex,SINGLE_MAX,SINGLE_DIVISOR,scoreObject);
    else if (diff < TRIPPLE_MAX)
        return findGreatestPointsWithinTerminalThreshold(remainingScore,turnIndex,TRIPPLE_MAX,scoreObject);
    else if (diff >= TRIPPLE_MAX)
        return writeToScoreObject(remainingScore,TRIPPLE_MAX,TRIPPLE_DIVISOR,turnIndex,scoreObject);
    return false;
}

bool DartsCreateFinishes::findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                                            const int &threshold, const int &divisor,
                                                            ScoreModel *s) const
{
    for (int points = threshold; points > 0; points -= divisor) {
        auto endScore = remainingScore - points;
        if (endScore <= TERMINAL_LIMIT && endScore % TERMINAL_DIVISOR == 0)
            return writeToScoreObject(remainingScore,points,divisor,turnIndex,s);
        else if (endScore >= TERMINAL_LIMIT)
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
        if (endScore < TERMINAL_LIMIT && endScore >= TERMINAL_DIVISOR) {
            if (points % TERMINAL_DIVISOR == 0 && points <= DOUBLE_MAX)
                return writeToScoreObject(remainingScore, points, DOUBLE_DIVISOR, turnIndex, s);
            else if (points % TRIPPLE_DIVISOR == 0 && points <= TRIPPLE_MAX)
                return writeToScoreObject(remainingScore, points, TRIPPLE_DIVISOR, turnIndex, s);
        }
    }
    return false;
}

bool DartsCreateFinishes::findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex,ScoreModel *s) const
{
    for (int points = TRIPPLE_MAX; points > 0; points -= TRIPPLE_DIVISOR) {
        auto endScore = remainingScore - points;
        if (endScore % 2 == 0 && endScore <= UPPER_LIMIT)
            return writeToScoreObject(remainingScore, points, TRIPPLE_DIVISOR, turnIndex, s);
    }
    return false;
}

bool DartsCreateFinishes::updateScoreObject(char stringIdentifier,int value,int index,ScoreModel *s) const
{
    if (value < 0)
        return false;
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
    return true;
}

bool DartsCreateFinishes::writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                                            const int &turnIndex, ScoreModel *s) const
{
    auto newScore = remainingScore - points;
    if (newScore == 0)
        return true;

    auto turnScore = points/divisor;
    auto identifier = identifierByDivisor(divisor);
    auto result = updateScoreObject(identifier, turnScore, turnIndex, s);
    return result ? suggestion(newScore, turnIndex + 1, s) : false;
}

QString DartsCreateFinishes::toString(ScoreModel *s) const
{
    QString result;
    for (int i = 0; i < ATTEMPTS; ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
    }
    return result;
}
