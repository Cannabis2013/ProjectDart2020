#include "dscplayerscontext.h"
#include <qdebug.h>
#include <DartsController/Models/dcinput.h>

void DSCPlayersContext::updateScore(const DCInput &input)
{
    try {
        auto playerScore = &getPlayerScoreByName(input.playerName);
        playerScore->remaining = input.remScore;
    }  catch (const char *msg) {
        qDebug() << msg;
        throw msg;
    }
}

void DSCPlayersContext::updateScores(const QVector<DCInput> &inputs)
{
    for (const auto &input : inputs) {
        auto scoreModel = &getPlayerScoreByName(input.playerName);
        if(input.remScore < scoreModel->remaining)
            scoreModel->remaining = input.remScore;
    }
}

void DSCPlayersContext::reset(const int &initRemScore)
{
    for (auto &scoreModel : _players)
        scoreModel.remaining = initRemScore;
}

DSCPlayersContext::Players &DSCPlayersContext::players()
{
    return _players;
}

DCPlayer &DSCPlayersContext::player(const QString &name) {
    return getPlayerScoreByName(name);
}

DCPlayer &DSCPlayersContext::player(const int &idx)
{
    return _players[idx];
}

DSCPlayersContext::Players DSCPlayersContext::players() const {return _players;}

bool DSCPlayersContext::status(const QString &) const
{
    return true;
}

void DSCPlayersContext::updateStatus(const DCInput &) {}

int DSCPlayersContext::count() const {return _players.count();}

void DSCPlayersContext::addPlayers(const Players &players)
{
    _players = players;
}

DCPlayer &DSCPlayersContext::getPlayerScoreByName(const QString &name)
{
    for (auto &scoreModel : _players) {
        if(scoreModel.name == name)
            return scoreModel;
    }
    throw "NO MODEL FOUND!";
}

DCPlayer DSCPlayersContext::getPlayerScoreByName(const QString &name) const
{
    for (auto &scoreModel : _players) {
        if(scoreModel.name == name)
            return scoreModel;
    }
    throw "NO MODEL FOUND!";
}
