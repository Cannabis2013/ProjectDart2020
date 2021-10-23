#ifndef DPCSCORESTATS_H
#define DPCSCORESTATS_H
#include "DartsController/DCInputStatsSLAs/idcscorestats.h"
#include <qregexp.h>
#include <math.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
class DPCScoreStats : public IDCScoreStats
{
public:
    void initialize(const QVector<DCPlayer> &players) override
    {
        for (const auto &player : players) {
            DCPlayerStat entity;
            entity.playerId = player.id;
            _playerStats << entity;
        }
    }
    void updatePlayerStats(DCInput &input, const IDCIndexController *indexService,
                               const IDCScoresService *, const int &initialScore) override
    {
        auto stats = getEntityFromId(input.playerId);
        checkAndSetScoreRange(stats,input.score);
        stats.middle = scoreAverage(input.remainingScore,indexService,initialScore);
        auto index = getEntityIndexById(stats.playerId);
        _playerStats.replace(index,stats);
        setInputStats(input,stats);
    }
    void updatePlayerStat(const DCInput &input) override
    {
        auto index = getEntityIndexById(input.playerId);
        auto stats = toStatsModel(input);
        _playerStats.replace(index,stats);
    }
    virtual QVector<DCPlayerStat> playerStats() const override
    {
        return _playerStats;
    }
private:
    double scoreAverage(const int &remainingScore, const IDCIndexController *indexService, const int &initialScore) const
    {
        double totalScore =  initialScore - remainingScore;
        double attempts = indexService->roundIndex() * 3 + indexService->attemptIndex() - 2;
        double preciseAvg = totalScore / attempts;
        double decimalAverage = std::round(preciseAvg*100) / (double) 100;
        return toTwoDecimal(decimalAverage);
    }
    double toTwoDecimal(const double &value) const
    {
        QRegExp reg("\\d+.\\d{2}");
        auto pos = reg.indexIn(QString::number(value));
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
    DCPlayerStat getEntityFromId(const QUuid &id) const
    {
        for (auto i = 0; i <_playerStats.count();i++) {
            auto entity = _playerStats.at(i);
            if(entity.playerId == id)
                return entity;
        }
        return DCPlayerStat();
    }
    int getEntityIndexById(const QUuid &id) const
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
        return stats;
    }
    QVector<DCPlayerStat> _playerStats;
};
#endif // DCRANGECALC_H
