#include "finishconstructor.h"

FinishConstructor::Finishes *FinishConstructor::construct()
{
    Finishes *allTargetRows = new Finishes();
    for (int turnIndex = 1; turnIndex <= ATTEMPTS; ++turnIndex) {
        auto remainingTurns = ATTEMPTS - turnIndex;
        auto currentPointLimit = remainingTurns * TRIPPLE_MAX + BULLS;
        auto finish = new Finish;
        for (int remainingScore = DOUBLE_MULTIPLIER; remainingScore <= currentPointLimit;
             ++remainingScore) {
            ScoreModel score;
            if (!_construct(remainingScore, turnIndex, &score))
                continue;
            QString finishAsText;
            for (int i = 0; i < ATTEMPTS; ++i) {
                auto identifier = score.multiplier.at(i);
                auto pVal = score.pointValue.at(i);
                finishAsText += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
            }
            if (finishAsText != QString())
                finish->insert(remainingScore, finishAsText);
        }
        allTargetRows->append(finish);
    }
    return allTargetRows;
}

char FinishConstructor::multiplierToString(const int &divisor) const
{
    if (divisor >= 1 && divisor <= 3)
        return identifiers[divisor - 1];
    throw "Divisor not valid";
}

bool FinishConstructor::_construct(const int &remainingScore,
                                   const int &turnIndex,
                                   ScoreModel *scoreObject) const
{
    if (remainingScore > 170 || remainingScore < DOUBLE_MULTIPLIER)
        return false;
    else if (turnIndex < 1 || turnIndex > 3)
        return false;
    else if (turnIndex > ATTEMPTS)
        return false;

    if (remainingScore <= DOUBLE_MAX) {
        auto newScore = remainingScore;
        if (remainingScore % DOUBLE_MULTIPLIER == 0) {
            auto turnScore = remainingScore / DOUBLE_MULTIPLIER;
            auto identifier = multiplierToString(DOUBLE_MULTIPLIER);
            return updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
        } else {
            for (int point = SINGLE_MAX; point > 0; --point) {
                auto newRemaining = remainingScore - point;
                if (newRemaining < DOUBLE_MAX
                    && newRemaining > 0
                    && newRemaining % DOUBLE_MULTIPLIER == 0) {
                    newScore -= point;
                    updateScoreObject('S', point, turnIndex, scoreObject);
                    return _construct(newScore, turnIndex + 1, scoreObject);
                }
            }
        }
        return false;
    } else if (turnIndex == ATTEMPTS && remainingScore != BULLS)
        return false;
    if (remainingScore == BULLS)
        return updateScoreObject('S', BULLS, turnIndex, scoreObject);

    auto diff = remainingScore - DOUBLE_MAX;

    if (diff >= TRIPPLE_MAX) {
        auto newScore = remainingScore - TRIPPLE_MAX;
        auto turnScore = TRIPPLE_MAX / TRIPPLE_MULTIPLIER;
        auto identifier = multiplierToString(TRIPPLE_MULTIPLIER);
        auto result = updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
        return result ? _construct(newScore, turnIndex + 1, scoreObject) : false;
    } else if (diff <= SINGLE_MAX) {
        for (int points = SINGLE_MAX; points > 0; points -= SINGLE_MULTIPLIER) {
            auto endScore = remainingScore - points;
            if (endScore <= DOUBLE_MAX && endScore % DOUBLE_MULTIPLIER == 0) {
                auto newScore = remainingScore - points;
                if (newScore == 0 && points != BULLS)
                    return true;
                auto turnScore = points / SINGLE_MULTIPLIER;
                auto identifier = multiplierToString(SINGLE_MULTIPLIER);
                auto result = updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
                return result ? _construct(newScore, turnIndex + 1, scoreObject) : false;
            } else if (endScore >= DOUBLE_MAX)
                return false;
        }
        return false;
    } else if (diff < TRIPPLE_MAX) {
        for (int points = TRIPPLE_MAX; points > 0; points--) {
            auto endScore = remainingScore - points;
            if (endScore < DOUBLE_MAX && endScore >= DOUBLE_MULTIPLIER) {
                if (points % DOUBLE_MULTIPLIER == 0 && points <= DOUBLE_MAX) {
                    auto newScore = remainingScore - points;
                    if (newScore == 0 && points != BULLS)
                        return true;
                    auto turnScore = points / DOUBLE_MULTIPLIER;
                    auto identifier = multiplierToString(DOUBLE_MULTIPLIER);
                    auto result = updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
                    return result ? _construct(newScore, turnIndex + 1, scoreObject) : false;
                } else if (points % TRIPPLE_MULTIPLIER == 0 && points <= TRIPPLE_MAX) {
                    auto newScore = remainingScore - points;
                    if (newScore == 0 && points != BULLS)
                        return true;

                    auto turnScore = points / TRIPPLE_MULTIPLIER;
                    auto identifier = multiplierToString(TRIPPLE_MULTIPLIER);
                    auto result = updateScoreObject(identifier, turnScore, turnIndex, scoreObject);
                    return result ? _construct(newScore, turnIndex + 1, scoreObject) : false;
                }
            }
        }
        return false;
    }
    return false;
}

bool FinishConstructor::updateScoreObject(char stringIdentifier,int value,int index,ScoreModel *s) const
{
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value >= 0 ? value : -1;
    return true;
}
