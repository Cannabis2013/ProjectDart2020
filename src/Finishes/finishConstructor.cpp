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
            ScoreModel score = _construct(remainingScore, turnIndex);
            QString finishAsText;
            for (int i = 0; i < score.multiplier.length(); ++i) {
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

FinishConstructor::ScoreModel FinishConstructor::_construct(const int &remainingScore,
                                                            const int &turnIndex) const
{
    if (remainingScore > 170 || remainingScore < DOUBLE_MULTIPLIER)
        return ScoreModel();
    else if (turnIndex < 1 || turnIndex > 3)
        return ScoreModel();
    else if (turnIndex > ATTEMPTS)
        return ScoreModel();

    ScoreModel scoreModel;
    int endScore, remaining = remainingScore;

    for (int index = turnIndex; index <= ATTEMPTS; index++) {
        if (remaining <= DOUBLE_MAX) {
            if (remaining % DOUBLE_MULTIPLIER == 0) {
                auto turnScore = remainingScore / DOUBLE_MULTIPLIER;
                auto identifier = multiplierToString(DOUBLE_MULTIPLIER);
                updateScoreObject(identifier, turnScore, index, &scoreModel);
            } else {
                for (int point = SINGLE_MAX; point > 0; --point) {
                    int newRemaining = remainingScore - point;
                    if (newRemaining < DOUBLE_MAX && newRemaining > 0
                        && newRemaining % DOUBLE_MULTIPLIER == 0) {
                        remaining -= point;
                        updateScoreObject('S', point, index, &scoreModel);
                    }
                }
            }
        } else if (remaining == BULLS) {
            updateScoreObject('S', BULLS, turnIndex, &scoreModel);
        } else {
            auto diff = remaining - DOUBLE_MAX;

            if (diff >= TRIPPLE_MAX) {
                remaining = remainingScore - TRIPPLE_MAX;
                auto turnScore = TRIPPLE_MAX / TRIPPLE_MULTIPLIER;
                auto identifier = multiplierToString(TRIPPLE_MULTIPLIER);
                updateScoreObject(identifier, turnScore, turnIndex, &scoreModel);
            } else if (diff <= SINGLE_MAX) {
                for (int points = SINGLE_MAX; points > 0; points -= SINGLE_MULTIPLIER) {
                    endScore = remainingScore - points;
                    if (endScore <= DOUBLE_MAX && endScore % DOUBLE_MULTIPLIER == 0) {
                        auto newScore = remainingScore - points;
                        if (newScore == 0 && points != BULLS)
                            return ScoreModel();
                        auto turnScore = points / SINGLE_MULTIPLIER;
                        auto identifier = multiplierToString(SINGLE_MULTIPLIER);
                        updateScoreObject(identifier, turnScore, turnIndex, &scoreModel);
                    }
                }
            } else if (diff < TRIPPLE_MAX) {
                for (int points = TRIPPLE_MAX; points > 0; points--) {
                    endScore = remainingScore - points;
                    if (endScore < DOUBLE_MAX && endScore >= DOUBLE_MULTIPLIER) {
                        if (points % DOUBLE_MULTIPLIER == 0 && points <= DOUBLE_MAX) {
                            remaining = remainingScore - points;
                            if (remaining == 0 && points != BULLS)
                                return ScoreModel();
                            auto turnScore = points / DOUBLE_MULTIPLIER;
                            auto identifier = multiplierToString(DOUBLE_MULTIPLIER);
                            updateScoreObject(identifier, turnScore, turnIndex, &scoreModel);
                        } else if (points % TRIPPLE_MULTIPLIER == 0 && points <= TRIPPLE_MAX) {
                            auto newScore = remainingScore - points;
                            if (newScore == 0 && points != BULLS)
                                return ScoreModel();

                            auto turnScore = points / TRIPPLE_MULTIPLIER;
                            auto identifier = multiplierToString(TRIPPLE_MULTIPLIER);
                            updateScoreObject(identifier, turnScore, turnIndex, &scoreModel);
                        }
                    }
                }
            }
        }
    }
    return scoreModel;
}

void FinishConstructor::updateScoreObject(char stringIdentifier,
                                          int value,
                                          int index,
                                          ScoreModel *s) const
{
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value >= 0 ? value : -1;
}
