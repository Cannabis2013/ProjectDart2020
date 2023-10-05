#include "dartsscores.h"
#include "src/DartsController/scores/scoresio.h"

DartsScores::DartsScores(IDartsIndexes* indexes, IDartPlayers* players, IDartInputs* inputs):
        _indexes(indexes),_players(players), _inputs(inputs){
        _scoresIO = new ScoresIO("playerScores.dat");
}

void DartsScores::init(const int& playersCount)
{
        _scores = QVector<int>(playersCount,501);
}

void DartsScores::init()
{
        _scores = _scoresIO->fromFile();
}

void DartsScores::reset()
{
        _scores = QVector<int>();
}

DartsScore DartsScores::update(DartInput input)
{
        auto playerIndex = _indexes->index().playerIndex();
        auto playerName = _players->name(playerIndex);
        auto scoreValue = inputScore(input);
        auto currentScore = _scores.at(playerIndex);
        auto newScore = currentScore - scoreValue;
        _scores.replace(playerIndex,newScore);
        _scoresIO->toFile(_scores);
        return DartsScore(playerName,newScore);
}

DartsScore DartsScores::update()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto turnIndex =_indexes->turnIndex();
        auto playerName = _players->name(playerIndex);
        auto playerInputs = _inputs->inputs(playerName,turnIndex);
        auto playerScore = totalScore(playerInputs);
        _scores.replace(playerIndex,playerScore);
        _scoresIO->toFile(_scores);
        return DartsScore(playerName,playerScore);
}

DartsScore DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto playerName = _players->name(playerIndex);
        auto playerScore = _scores.at(playerIndex);
        return DartsScore(playerName,playerScore);
}

QVector<int> DartsScores::scores()
{
        return _scores;
}

int DartsScores::totalScore(const QList<DartInput>& inputs)
{
        int sum = 0;
        for (auto& input : qAsConst(inputs))
                sum += inputScore(input);
        return sum;
}

int DartsScores::inputScore(const DartInput& input) const
{
        auto multiplier = modMultiplier(input.mod());
        return  input.point()*multiplier;
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
