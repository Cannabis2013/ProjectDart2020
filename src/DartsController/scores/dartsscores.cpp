#include "dartsscores.h"

DartsScores::DartsScores(IDartsIndexes* indexes, IDartPlayers* players, IDartsInputs* inputs):
        _indexes(indexes),_players(players), _inputs(inputs){
        _scoresIO = new ScoresIO("playerScores.dat");
}

void DartsScores::init()
{
        _scores.clear();
        auto names = _players->names();
        for (const auto &name : names)
                _scores << DartsInternalScore(name);
}

void DartsScores::reset()
{
        auto names = _players->names();
        for (const auto &name : names)
                _scores << DartsInternalScore(name);
}

DartsPlayerScore DartsScores::update(const Input& input)
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internalScore = calculatedScore(input,_scores[playerIndex]);
        _scores.replace(playerIndex,internalScore);
        _scoresIO->toFile(_scores);
        return DartsPlayerScore(internalScore);
}

DartsPlayerScores DartsScores::update()
{
        _scores = calculatedScores();
        _scoresIO->toFile(_scores);
        return DartsPlayerScores(_scores);
}

DartsPlayerScore DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}

QList<DartsInternalScore> DartsScores::calculatedScores()
{
        QList<DartsInternalScore> scores;
        auto turnIndex = _indexes->turnIndex();
        auto names = _players->names();
        for (const auto &name : qAsConst(names)) {
                int score = 501;
                auto inputs = _inputs->inputs(name,turnIndex);
                for (auto& input : qAsConst(inputs))
                        score -= inputScore(input.mod(),input.point());
                scores.append(DartsInternalScore(name,score));
        }
        return scores;
}

DartsInternalScore DartsScores::calculatedScore(const DartsInputResponse& input, DartsInternalScore& current)
{
        auto scoreValue = inputScore(input.mod(),input.point());
        auto newScore = current.score() - scoreValue;
        auto playerIndex = _indexes->index().playerIndex();
        auto playerName = _players->name(playerIndex);
        return DartsInternalScore(playerName,newScore);
}

int DartsScores::inputScore(const QString &mod, const int &point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int DartsScores::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}

