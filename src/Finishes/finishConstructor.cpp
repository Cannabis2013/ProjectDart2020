#include "finishconstructor.h"

FinishConstructor::Finishes *FinishConstructor::construct()
{
    Finishes *allTargetRows = new Finishes();
    for (int turnIndex = 1; turnIndex <= ATTEMPTS; ++turnIndex) {
        auto remainingTurns = ATTEMPTS - turnIndex;
        auto maxRemaining = remainingTurns * TRIPPLE_MAX + BULLS;
        auto finish = new Finish;
        for (int remaining = 2; remaining <= maxRemaining; ++remaining) {
            ScoreModel score = _construct(remaining, turnIndex);
            QString finishAsString;
            for (int i = 0; i < score.multiplier.length(); ++i) {
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

ScoreModel FinishConstructor::_construct(const int &remainingScore, const int &turnIndex) const
{
    ScoreModel scoreModel;
    int remaining = remainingScore;
    for (int index = turnIndex; index <= ATTEMPTS; index++) {
        if (remaining > 170 || remaining < 2)
            return ScoreModel();
        if (turnIndex == 3 && remaining % 2 != 0 && remaining != BULLS)
            return ScoreModel();
        if (remaining <= DOUBLE_MAX && remaining % 2 == 0) {
            scoreModel.append('D', remaining / 2);
            return scoreModel;
        } else if (remaining <= DOUBLE_MAX) {
            for (int point = SINGLE_MAX; point > 0; --point) {
                auto newRemaining = remaining - point;
                if (newRemaining < DOUBLE_MAX && newRemaining > 0 && newRemaining % 2 == 0) {
                    remaining = newRemaining;
                    scoreModel.append('S', point);
                    break;
                }
            }
        } else if (remaining == BULLS) {
            scoreModel.append('S', BULLS);
            return scoreModel;
        } else {
            auto diff = remaining - DOUBLE_MAX;
            if (diff >= TRIPPLE_MAX && diff % 2 != 0) {
                for (int point = TRIPPLE_MAX; point >= 3; point -= 3) {
                    auto newDiff = diff - point;
                    if (newDiff % 2 == 0) {
                        scoreModel.append('T', point / 3);
                        remaining -= point;
                        break;
                    }
                }
            } else if (diff >= TRIPPLE_MAX) {
                remaining -= TRIPPLE_MAX;
                scoreModel.append('T', 20);
            } else if (diff <= SINGLE_MAX) {
                for (int points = SINGLE_MAX; points > 0; --points) {
                    auto newRemaining = remaining - points;
                    if (newRemaining <= DOUBLE_MAX && newRemaining % 2 == 0) {
                        if (newRemaining == 0)
                            return scoreModel;
                        remaining = newRemaining;
                        scoreModel.append('S', points);
                        break;
                    } else if (newRemaining >= DOUBLE_MAX)
                        return ScoreModel();
                }
            } else if (diff < TRIPPLE_MAX && diff % 2 != 0) {
                remaining -= 57;
                scoreModel.append('T', 19);
            } else if (diff < TRIPPLE_MAX) {
                for (int points = TRIPPLE_MAX; points > 0; points--) {
                    auto newRemaining = remaining - points;
                    if (newRemaining < DOUBLE_MAX && newRemaining >= 2) {
                        if (points % 2 == 0 && points <= DOUBLE_MAX) {
                            if (newRemaining == 0)
                                return scoreModel;
                            remaining = newRemaining;
                            scoreModel.append('D', points / 2);
                            break;
                        } else if (points % 3 == 0 && points <= TRIPPLE_MAX) {
                            if (newRemaining == 0 && points != 50)
                                return scoreModel;
                            remaining = newRemaining;
                            scoreModel.append('T', points / 3);
                            break;
                        }
                    }
                }
            }
        }
    }
    return ScoreModel();
}
