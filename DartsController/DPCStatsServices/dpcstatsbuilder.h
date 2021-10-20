#ifndef DPCSTATSBUILDER_H
#define DPCSTATSBUILDER_H
#include "DartsController/DCInputStatsSLAs/idcstatsbuilder.h"
#include <qregexp.h>
#include <math.h>
class DPCStatsBuilder : public IDCStatsBuilder
{
public:
    virtual void setPlayers(const QVector<DCPlayer> &players) override
    {
        for (const auto &player : players) {
            DCInputStat entity;
            entity.id = player.id;
            _entities << entity;
        }
    }
    virtual DCInputStat processScore(const DCInput &input, const IDCIndexService *indexService, const int &initialScore) override
    {
        auto entity = getEntityFromId(input.playerId);
        checkAndSetScoreRange(entity,input.score);
        entity.average = scoreAverage(input.remainingScore,indexService,initialScore);
        auto index = getEntityIndexById(entity.id);
        _entities.replace(index,entity);
        return entity;
    }
private:
    double scoreAverage(const int &remainingScore, const IDCIndexService *indexService, const int &initialScore) const
    {
        double totalScore =  initialScore - remainingScore;
        double attempts = indexService->roundIndex() * 3 + indexService->attemptIndex() - 2;
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
    void checkAndSetScoreRange(DCInputStat &entity, const int &score) const
    {
        auto lowScore = entity.lowest;
        auto highScore = entity.highest;
        if(lowScore > score)
            entity.lowest = score;
        else if(score > highScore)
            entity.highest = score;
    }
    DCInputStat getEntityFromId(const QUuid &id) const
    {
        for (auto i = 0; i <_entities.count();i++) {
            auto entity = _entities.at(i);
            if(entity.id == id)
                return entity;
        }
        return DCInputStat();
    }
    int getEntityIndexById(const QUuid &id) const
    {
        for (auto i = 0; i <_entities.count();i++) {
            auto entity = _entities.at(i);
            if(entity.id == id)
                return i;
        }
        return -1;
    }
    QVector<DCInputStat> _entities;
};
#endif // DCRANGECALC_H
