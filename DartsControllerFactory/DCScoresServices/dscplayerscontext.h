#ifndef DSCPLAYERSCONTEXT_H
#define DSCPLAYERSCONTEXT_H
#include "DCScoresSLAs/absdcplayersctx.h"
#include <qdebug.h>
#include "Models/dcplayer.h"
#include "Models/dcindex.h"
#include "Models/dcinput.h"
class DSCPlayersContext : public AbsDCPlayersCtx
{
public:
    DartsScoreModels &players() override {return _players;}
    virtual void updateScore(const DCInput &ipt) override
    {
        try {
            auto scoreModel = &getScoreModelByName(ipt.playerName);
            scoreModel->remScore = ipt.remScore;
        }  catch (const char *msg) {
            qDebug() << msg;
            throw msg;
        }
    }
    void updateScores(const QVector<DCInput> &inputs) override
    {
        for (const auto &input : inputs) {
            auto scoreModel = &getScoreModelByName(input.playerName);
            if(input.remScore < scoreModel->remScore)
                scoreModel->remScore = input.remScore;
        }
    }
    DCPlayer &player(const QString &name) override {return getScoreModelByName(name);}
    DCPlayer &player(const int &idx) override {return _players[idx];}
    void reset(const int &initRemScore) override
    {
        for (auto &scoreModel : _players)
            scoreModel.remScore = initRemScore;
    }
    DartsScoreModels players() const override {
        return _players;
    }
    virtual void set(const QStringList &names, const int &remScore) override
    {
        _players.clear();
        for (const auto &name : names)
            _players << DCPlayer(name,remScore,false);
    }
    virtual bool status(const QString &) const override {return true;}
    virtual void updateStatus(const DCInput &) override {}
    virtual int count() const override {return _players.count();}
private:
    DCPlayer &getScoreModelByName(const QString &name)
    {
        for (auto &scoreModel : _players) {
            if(scoreModel.name == name)
                return scoreModel;
        }
        throw "NO MODEL FOUND!";
    }
    DCPlayer getScoreModelByName(const QString &name) const
    {
        for (auto &scoreModel : _players) {
            if(scoreModel.name == name)
                return scoreModel;
        }
        throw "NO MODEL FOUND!";
    }
    DartsScoreModels _players;
};

#endif // DSCSCORESCONTEXT_H
