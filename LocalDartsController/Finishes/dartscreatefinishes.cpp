#include "dartscreatefinishes.h"

#include <DartsController/Finishes/idartsattemptsservice.h>
#include <DartsController/Finishes/idartsboundaries.h>
#include <DartsController/Finishes/idartsdivisorvalues.h>
#include <DartsController/Finishes/idartsfieldvalues.h>
#include <DartsController/Finishes/idartsmodidentifiers.h>
#include <DartsController/Finishes/idartsterminaldivisor.h>

IDartsCreateFinishes::AllTargetRows DartsCreateFinishes::constructRows() const
{
        AllTargetRows allTargetRows;
        for (int turnIndex = 1; turnIndex <= attemptsService()->attempts(); ++turnIndex) {
                auto remainingTurns = attemptsService()->attempts() - turnIndex;
                auto currentPointLimit = remainingTurns*boundaries()->trippleMaxValue() + fieldValues()->bullsEye();
                auto suggestions = new TargetRows;
                for (int i = divisors()->doubleDivisor(); i <= currentPointLimit; ++i) {
                        auto firstSuggestion = constructRow(i,turnIndex);
                        if(firstSuggestion != QString())
                                suggestions->insert(i,firstSuggestion);
                }
                allTargetRows << suggestions;
        }
        return allTargetRows;
}

QString DartsCreateFinishes::constructRow(const int &remainingScore, const int &turnIndex) const
{
            auto score = new ScoreModel;
            score->multiplier = QVector<char>(attemptsService()->attempts(),'\0');
            score->pointValue = QVector<int>(attemptsService()->attempts(),0);
            bool hasADeterminedPath;
            try {
                    hasADeterminedPath = suggestion(remainingScore,turnIndex,score);
            } catch (std::exception *e) {
                    return QString();
            }
            if(hasADeterminedPath)
                    return toString(score);
            return QString();
}

bool DartsCreateFinishes::suggestion(const int &remainingScore, const int &turnIndex,
                                         ScoreModel *scoreObject) const
{
        /*
         * Evaluate constrains
         */
        if(!evaluateConstraints(remainingScore,turnIndex,attemptsService()->attempts()))
                return false;
        /*
         * The terminal state
         *
         * The algorithm checks if the remaining score is below the terminal threshold, and if that's the case,
         *  how to get to terminal point. If not, the algorithm proceeds to find another way.
         */
        if(remainingScore <= thresholds()->terminalThreshold())
            return isWithinTerminalThreshold(remainingScore,turnIndex,scoreObject);
        else if(turnIndex == attemptsService()->attempts() && remainingScore != fieldValues()->bullsEye())
            return false;
        /*
         * This is the pathfinding state where the algorithm tries to determine, if exists, the route.
         * If this is the last round, no ways exist, and the algorithm terminates with false.
         */
        if(remainingScore == fieldValues()->bullsEye())
            return writeToScoreObject(remainingScore,fieldValues()->bullsEye(),divisors()->singleDivisor(),turnIndex,scoreObject);

        if(remainingScore >= thresholds()->upperThresholdValue() && turnIndex == 1)
            return determineRouteByThresholdDiff(remainingScore,turnIndex,scoreObject);
        else
            return determineRouteByDiff(remainingScore,turnIndex,scoreObject);
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
    if(remainingScore > 170 || remainingScore < terminalDivisor()->divisor())
        return false;
    else if(turnIndex < 1 || turnIndex > 3)
        return false;
    else if(totalTurns < turnIndex)
        return false;
    else
        return true;
}

bool DartsCreateFinishes::isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   ScoreModel *scoreObject) const
{
    auto newScore = remainingScore;
    if(isDivisor(remainingScore,terminalDivisor()->divisor()))
    {
        auto turnScore = remainingScore/terminalDivisor()->divisor();
        try {
            auto identifier = identifiers()->identifierByDivisor(terminalDivisor()->divisor());
            updateScoreObject(identifier,turnScore,turnIndex,scoreObject);
            return true;
        } catch (std::out_of_range *e) {
            throw e;
        }
    }
    else
    {
        for (int i = boundaries()->singleMaxValue(); i > 0; --i) {
            auto endScore = remainingScore - i;
            if(endScore < thresholds()->terminalThreshold() && endScore > 0  && endScore % terminalDivisor()->divisor() == 0)
            {
                newScore -= i;
                try {
                    updateScoreObject('S',i,turnIndex,scoreObject);
                    return suggestion(newScore,turnIndex + 1,scoreObject);
                }  catch (const char *e) {
                    throw e;
                }
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
    auto thresholdDiff = remainingScore - thresholds()->upperThresholdValue();
    if(thresholdDiff == 0) // If the remaining score is spot on 110
        return writeToScoreObject(remainingScore,boundaries()->trippleMaxValue(),divisors()->trippleDivisor(),turnIndex,s);
    else if(thresholdDiff == fieldValues()->bullsEye() || thresholdDiff == fieldValues()->bull()) // Bullseye
        return writeToScoreObject(remainingScore,thresholdDiff,divisors()->singleDivisor(),turnIndex,s);
    else if(thresholdDiff <= boundaries()->singleMaxValue())
        return writeToScoreObject(remainingScore,thresholdDiff,divisors()->singleDivisor(),turnIndex,s);
    else if(thresholdDiff <= boundaries()->doubleMaxValue())
    {
        if(isDivisor(thresholdDiff,divisors()->doubleDivisor()))
            return writeToScoreObject(remainingScore,thresholdDiff,divisors()->doubleDivisor(),turnIndex,s);
        else if(isDivisor(thresholdDiff,divisors()->trippleDivisor()))
            return writeToScoreObject(remainingScore,thresholdDiff,divisors()->trippleDivisor(),turnIndex,s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
    }
    else if(thresholdDiff <= boundaries()->trippleMaxValue())
    {
        if(isDivisor(thresholdDiff,divisors()->trippleDivisor()))
            return writeToScoreObject(remainingScore,thresholdDiff,divisors()->trippleDivisor(),turnIndex,s);
        else if(!isEven(thresholdDiff))
            return findGreatestOddDivisibleByThree(remainingScore,turnIndex,s);
        else if(isEven(thresholdDiff))
            return writeToScoreObject(remainingScore,boundaries()->trippleMaxValue(),divisors()->trippleDivisor(),turnIndex,s);
    }
    return false;
}

bool DartsCreateFinishes::determineRouteByDiff(const int &remainingScore, const int &turnIndex,
                                              ScoreModel *scoreObject) const
{
    auto diff = remainingScore - thresholds()->terminalThreshold();

    if(diff <= boundaries()->singleMaxValue())
        return findGreatestPointsWithinThreshold(remainingScore,turnIndex,boundaries()->singleMaxValue(),divisors()->singleDivisor(),scoreObject);
    else if(diff < boundaries()->trippleMaxValue())
        return findGreatestPointsWithinTerminalThreshold(remainingScore,turnIndex,boundaries()->trippleMaxValue(),scoreObject);
    else if(diff >= boundaries()->trippleMaxValue())
        return writeToScoreObject(remainingScore,boundaries()->trippleMaxValue(),divisors()->trippleDivisor(),turnIndex,scoreObject);
    return false;
}

bool DartsCreateFinishes::findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                                            const int &threshold, const int &divisor,
                                                            ScoreModel *s) const
{
    for (int points = threshold; points > 0; points -= divisor) {
        auto endScore = remainingScore - points;
        if(endScore <= thresholds()->terminalThreshold() && endScore % terminalDivisor()->divisor() == 0)
            return writeToScoreObject(remainingScore,points,divisor,turnIndex,s);
        else if(endScore >= thresholds()->terminalThreshold())
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
        if(endScore < thresholds()->terminalThreshold() && endScore >= terminalDivisor()->divisor())
        {
            if(points % terminalDivisor()->divisor() == 0 && points <= boundaries()->doubleMaxValue())
                return writeToScoreObject(remainingScore,points,divisors()->doubleDivisor(),turnIndex,s);
            else if(points % divisors()->trippleDivisor() == 0 && points <= boundaries()->trippleMaxValue())
                return writeToScoreObject(remainingScore,points,divisors()->trippleDivisor(),turnIndex,s);
        }
    }
    return false;
}

bool DartsCreateFinishes::findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex,ScoreModel *s) const
{
    for (int points = boundaries()->trippleMaxValue(); points > 0; points -= divisors()->trippleDivisor()) {
        auto endScore = remainingScore - points;
        if(isEven(endScore) && endScore <= thresholds()->upperThresholdValue())
            return writeToScoreObject(remainingScore,points,divisors()->trippleDivisor(),turnIndex,s);
    }
    return false;
}

void DartsCreateFinishes::updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s) const
{
    if(value < 0)
        throw new std::out_of_range("Value out of bounds");
    s->multiplier[index - 1] = stringIdentifier;
    s->pointValue[index - 1] = value;
}

bool DartsCreateFinishes::writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                                            const int &turnIndex, ScoreModel *s) const
{
    auto newScore = remainingScore - points;
    auto turnScore = points/divisor;
    auto identifier = identifiers()->identifierByDivisor(divisor);
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
    auto result = integer % 2 == 0;
    return result;
}

QString DartsCreateFinishes::toString(ScoreModel *s) const
{
    QString result;
    for (int i = 0; i < attemptsService()->attempts(); ++i) {
        auto identifier = s->multiplier.at(i);
        auto pVal = s->pointValue.at(i);
        result += identifier == '\0' ? "" : identifier + QString::number(pVal) + " ";
    }
    return result;
}
