#include "dpcplayerscontext.h"
#include <qdebug.h>
#include <DartsController/Models/dcinput.h>
#include <DartsController/Models/dcplayer.h>

DPCPlayersContext::Players &DPCPlayersContext::players() {return _players;}

void DPCPlayersContext::updateScore(const DCInput &input)
{
        try {
                auto scoreModel = &getScoreModelByName(input.playerName);
                scoreModel->remaining = input.remScore;
        }  catch (const char *msg) {
                qDebug() << msg;
                throw msg;
        }
}

void DPCPlayersContext::updateScores(const QVector<DCInput> &inputs)
{
    for (const auto &input : inputs) {
        auto scoreModel = &getScoreModelByName(input.playerName);
        if(input.remScore < scoreModel->remaining)
            scoreModel->remaining = input.remScore;
    }
}

DPCPlayersContext::Player &DPCPlayersContext::player(const QString &name) {return getScoreModelByName(name);}
DPCPlayersContext::Player &DPCPlayersContext::player(const int &idx) {return _players[idx];}

void DPCPlayersContext::reset(const int &initRemScore)
{
    for (auto &scoreModel : _players)
        scoreModel.remaining = initRemScore;
}

DPCPlayersContext::Players DPCPlayersContext::players() const {return _players;}

void DPCPlayersContext::addPlayers(const Players &players) {_players = players;}

bool DPCPlayersContext::status(const QString &name) const
{
    auto s = getScoreModelByName(name);
    return s.in;
}

void DPCPlayersContext::updateStatus(const DCInput &ipt)
{
    auto pModel = &getScoreModelByName(ipt.playerName);
    pModel->in = ipt.inGame;
}

int DPCPlayersContext::count() const {return _players.count();}

DCPlayer &DPCPlayersContext::getScoreModelByName(const QString &name)
{
    for (auto &scoreModel : _players) {
        if(scoreModel.name == name)
            return scoreModel;
    }
    throw "NO MODEL FOUND!";
}

DCPlayer DPCPlayersContext::getScoreModelByName(const QString &name) const
{
    for (auto &scoreModel : _players) {
        if(scoreModel.name == name)
            return scoreModel;
    }
    throw "NO MODEL FOUND!";
}
