#include "scorescalculator.h"

Score ScoresCalculator::calculate(const QString& name, const QList<Input>& inputs, const int& initialScore){
        int score = initialScore;
        for (auto& input : inputs)
                score -= inputScore(input.mod(), input.point());
        if (score < 0)
                return Score(name);
        return Score(name, score);
}

Score ScoresCalculator::calculate(const Input& input, const Score& score, const QString& name){
        auto scoreValue = inputScore(input.mod(),input.point());
        auto newScore = score.score() - scoreValue;
        if (newScore < 0)
                return Score(name);
        return Score(name,newScore);
}

int ScoresCalculator::inputScore(const QString& mod, const int& point) const{
        return point * modMultiplier(mod);
}

int ScoresCalculator::modMultiplier(QString mod) const{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
