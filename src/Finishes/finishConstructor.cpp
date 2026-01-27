#include "finishconstructor.h"

FinishConstructor::Finishes *FinishConstructor::construct()
{
    Finishes *allTargetRows = new Finishes();
    for (int turnIndex = 1; turnIndex <= ATTEMPTS; ++turnIndex) {
        auto remainingTurns = ATTEMPTS - turnIndex;
        auto maxRemaining = remainingTurns * TRIPPLE_MAX + BULLS;
        auto finish = new Finish;
        for (int remaining = DOUBLE_MULTIPLIER; remaining <= maxRemaining; ++remaining) {
            ScoreModel score = _construct(remaining, turnIndex);
            QString finishAsString;
            for (int i = 0; i < score.count; ++i) {
                auto identifier = score.multiplier.at(i);
                auto pointValue = score.pointValue.at(i);
                finishAsString += QString("%1%2 ").arg(identifier).arg(pointValue);
            }
            if (finishAsString != QString())
                finish->insert(remaining, finishAsString);
        }
        allTargetRows->append(finish);
    }
    return allTargetRows;
}

FinishConstructor::ScoreModel FinishConstructor::_construct(const int &remainingScore,
                                                            const int &turnIndex) const
{
    ScoreModel scoreModel;
    int remaining = remainingScore;

    for (int index = turnIndex; index <= ATTEMPTS; index++) {
        if (remaining > 170 || remaining < DOUBLE_MULTIPLIER)
            return ScoreModel();

        if (remaining <= DOUBLE_MAX) {
            if (remaining % DOUBLE_MULTIPLIER == 0) {
                auto pointValue = remaining / DOUBLE_MULTIPLIER;
                auto identifier = identifiers[DOUBLE_MULTIPLIER];
                scoreModel.append(identifier, pointValue);
                return scoreModel;
            } else {
                for (int point = SINGLE_MAX; point > 0; --point) {
                    auto newRemaining = remaining - point;
                    if (newRemaining < DOUBLE_MAX && newRemaining > 0
                        && newRemaining % DOUBLE_MULTIPLIER == 0) {
                        remaining = newRemaining;
                        scoreModel.append('S', point);
                        break;
                    }
                }
            }
        } else if (remaining == BULLS) {
            scoreModel.append('S', BULLS);
            return scoreModel;
        } else {
            auto diff = remaining - DOUBLE_MAX;
            if (diff >= TRIPPLE_MAX) {
                remaining -= TRIPPLE_MAX;
                auto pointValue = TRIPPLE_MAX / TRIPPLE_MULTIPLIER;
                auto identifier = identifiers[TRIPPLE_MULTIPLIER];
                scoreModel.append(identifier, pointValue);
            } else if (diff <= SINGLE_MAX) {
                for (int points = SINGLE_MAX; points > 0; points -= SINGLE_MULTIPLIER) {
                    auto newRemaining = remaining - points;
                    if (newRemaining <= DOUBLE_MAX && newRemaining % DOUBLE_MULTIPLIER == 0) {
                        if (newRemaining == 0)
                            return scoreModel;
                        remaining = newRemaining;
                        auto pointValue = points / SINGLE_MULTIPLIER;
                        auto identifier = identifiers[SINGLE_MULTIPLIER];
                        scoreModel.append(identifier, pointValue);
                        break;
                    } else if (newRemaining >= DOUBLE_MAX)
                        return ScoreModel();
                }
            } else if (diff < TRIPPLE_MAX) {
                for (int points = TRIPPLE_MAX; points > 0; points--) {
                    auto newRemaining = remaining - points;
                    if (newRemaining < DOUBLE_MAX && newRemaining >= DOUBLE_MULTIPLIER) {
                        if (points % DOUBLE_MULTIPLIER == 0 && points <= DOUBLE_MAX) {
                            if (newRemaining == 0)
                                return scoreModel;
                            remaining = newRemaining;
                            auto pointValue = points / DOUBLE_MULTIPLIER;
                            auto identifier = identifiers[DOUBLE_MULTIPLIER];
                            scoreModel.append(identifier, pointValue);
                            break;
                        } else if (points % TRIPPLE_MULTIPLIER == 0 && points <= TRIPPLE_MAX) {
                            if (newRemaining == 0 && points != BULLS)
                                return scoreModel;
                            remaining = newRemaining;
                            auto pointValue = points / TRIPPLE_MULTIPLIER;
                            auto identifier = identifiers[TRIPPLE_MULTIPLIER];
                            scoreModel.append(identifier, pointValue);
                            break;
                        }
                    }
                }
            }
        }
    }
    return ScoreModel();
}
