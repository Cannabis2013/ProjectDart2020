#ifndef DCIPTCONVERTER_H
#define DCIPTCONVERTER_H
#include "DartsController/DCInputSLAs/abstractdciptconverter.h"
#include <qvector.h>
class DCIptConverter : public AbstractDCIptConverter
{
public:
    DCIptConverter(AbstractDCInputBuilder *builder):
        AbstractDCIptConverter(builder){}
    DCInput convert(AbstractDartsInput *input, const int &initRemScore, const DCPlayer &player) const override
    {
        DCInput ipt;
        if(input != nullptr)
            ipt =  create(input); // Copy values from input to ipt
        else
            ipt = iptBuilder()->create(initRemScore,player); // Create input model with default values
        return ipt;
    }
    QVector<DCInput> convert(const QVector<AbstractDartsInput *> &inputs) const override
    {
        QVector<DCInput> list;
        for (const auto &input : inputs)
            list << create(input);
        return list;
    }
    DIptVals convert(DCInput &input) const override
    {
        DIptVals iptVals;
        iptVals.score = input.score;
        iptVals.point = input.point;
        iptVals.remainingScore = input.remScore;
        iptVals.roundIndex = input.roundIndex;
        iptVals.setIndex = input.setIndex;
        iptVals.attempt = input.attempt;
        iptVals.playerName = input.playerName;
        iptVals.min = input.min;
        iptVals.mid = input.mid;
        iptVals.max = input.max;
        iptVals.approved = input.approved;
        iptVals.inGame = input.inGame;
        return iptVals;
    }
private:
    DCInput create(AbstractDartsInput *ipt) const
    {
        DCInput cIpt;
        cIpt.score = ipt->score();
        cIpt.point = ipt->point();
        cIpt.remScore = ipt->remainingScore();
        cIpt.roundIndex = ipt->roundIndex();
        cIpt.setIndex = ipt->setIndex();
        cIpt.attempt = ipt->attempt();
        cIpt.playerName = ipt->playerName();
        cIpt.min = ipt->currentMinimum();
        cIpt.mid = ipt->middleValue();
        cIpt.max = ipt->currentMaximum();
        cIpt.approved = ipt->approved();
        cIpt.inGame = ipt->inGame();
        return cIpt;
    }
};
#endif // DCIPTCONVERTER_H
