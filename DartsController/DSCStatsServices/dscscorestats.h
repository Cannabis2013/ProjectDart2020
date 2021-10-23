#ifndef DSCSCORESTATS_H
#define DSCSCORESTATS_H
#include "DartsController/DCInputStatsSLAs/idcscorestats.h"
#include <qregexp.h>
#include <math.h>
class DSCScoreStats : public IDCScoreStats
{
public:
    virtual void initialize(const QVector<DCPlayer> &players) override
    {
        for (const auto &player : players) {
            DCPlayerStat entity;
            entity.playerId = player.id;
            _playerStats << entity;
        }
    }
    virtual void updatePlayerStats(DCInput &input, const IDCIndexController *indexService,
                                  const IDCScoresService *scoresService, const int &initialScore) override
    {
        auto stats = getPlayerStatsById(input.playerId);
        checkAndSetScoreRange(stats,input.score);
        auto currentRemaining = scoresService->scoreModel(input.playerId).remainingScore;
        auto remainingScore = currentRemaining - input.score;
        stats.middle = scoreAverage(remainingScore,indexService,initialScore);
        auto index = getPlayerStatsIndexById(stats.playerId);
        _playerStats.replace(index,stats);
        setInputStats(input,stats);
    }
    virtual void updatePlayerStat(const DCInput &input) override
    {
        auto index = getPlayerStatsIndexById(input.playerId);
        _playerStats.replace(index,toStatsModel(input));
    }
    QVector<DCPlayerStat> playerStats() const override
    {
        return _playerStats;
    }
private:
    double scoreAverage(const int &remainingScore, const IDCIndexController *indexService, const int &initialScore) const
    {
        double totalScore =  initialScore - remainingScore;
        double attempts = indexService->roundIndex()*3;
        double preciseAvg = totalScore / attempts;
        double decimalAverage = std::round(preciseAvg*100) / (double) 100;
        return toTwoDecimal(decimalAverage);
    }
    double toTwoDecimal(const double &value) const
    {
        auto stringNumber = QString::number(value);
        QRegExp reg("\\d+.\\d{2}");
        auto pos = reg.indexIn(stringNumber);
        if(pos == -1)
            return value;
        return reg.cap(0).toDouble();
    }
    void checkAndSetScoreRange(DCPlayerStat &entity, const int &score) const
    {
        auto lowScore = entity.min;
        auto highScore = entity.max;
        if(lowScore > score || lowScore == -1)
            entity.min = score;
        if(score > highScore)
            entity.max = score;
    }
    DCPlayerStat getPlayerStatsById(const QUuid &id) const
    {
        for (auto i = 0; i <_playerStats.count();i++) {
            auto playerStat = _playerStats.at(i);
            if(playerStat.playerId == id)
                return playerStat;
        }
        return DCPlayerStat();
    }
    int getPlayerStatsIndexById(const QUuid &id) const
    {
        for (auto i = 0; i <_playerStats.count();i++) {
            auto entity = _playerStats.at(i);
            if(entity.playerId == id)
                return i;
        }
        return -1;
    }
    void setInputStats(DCInput &input, const DCPlayerStat &stats) const
    {
        input.middle = stats.middle;
        input.min = stats.min;
        input.max = stats.max;
    }
    DCPlayerStat toStatsModel(const DCInput &input) const
    {
        DCPlayerStat stats;
        stats.middle = input.middle;
        stats.min = input.min;
        stats.max = input.max;
        stats.playerId = input.playerId;
        return stats;
    }
    QVector<DCPlayerStat> _playerStats;
};
#endif // DCRANGECALC_H
