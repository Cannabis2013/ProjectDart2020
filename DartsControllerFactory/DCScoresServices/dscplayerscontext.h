#ifndef DSCPLAYERSCONTEXT_H
#define DSCPLAYERSCONTEXT_H
#include "DCScoresSLAs/idcplayermanager.h"
#include <qvector.h>
#include "Models/dcplayer.h"
class DSCPlayersContext : public IDCPlayerManager<DCPlayer,DCInput>
{
public:
    Players &players() override;
    virtual void updateScore(const DCInput &ipt) override;
    void updateScores(const QVector<DCInput> &inputs) override;
    DCPlayer &player(const QString &name) override;
    DCPlayer &player(const int &idx) override;
    void reset(const int &initRemScore) override;
    Players players() const override;
    virtual void addPlayers(const Players &players) override;
    virtual bool status(const QString &) const override;
    virtual void updateStatus(const DCInput &) override;
    virtual int count() const override;
private:
    DCPlayer &getScoreModelByName(const QString &name);
    DCPlayer getScoreModelByName(const QString &name) const;
    Players _players;
};

#endif // DSCSCORESCONTEXT_H
