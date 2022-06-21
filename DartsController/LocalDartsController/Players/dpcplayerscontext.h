#ifndef DPCPLAYERSCONTEXT_H
#define DPCPLAYERSCONTEXT_H

#include <qvector.h>
#include <DartsController/Contracts/Players/idcplayermanager.h>

struct DCInput;
struct DCPlayer;

class DPCPlayersContext : public IDCPlayerManager<DCPlayer,DCInput>
{
public:
    Players &players() override;
    virtual void updateScore(const DCInput &input) override;
    void updateScores(const QVector<DCInput> &inputs) override;
    Player &player(const QString &name) override;
    DCPlayer &player(const int &idx) override;
    virtual void reset(const int &initRemScore) override;
    Players players() const override;
    void addPlayers(const Players &players) override;
    virtual bool status(const QString &name) const override;
    virtual void updateStatus(const DCInput &ipt) override;
    virtual int count() const override;
private:
    DCPlayer &getScoreModelByName(const QString &name);
    DCPlayer getScoreModelByName(const QString &name) const;
    Players _players;
};
#endif // DARTSSCORES_H
