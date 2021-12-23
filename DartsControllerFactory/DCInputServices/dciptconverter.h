#ifndef DCIPTCONVERTER_H
#define DCIPTCONVERTER_H
#include "DCInputSLAs/abstractdciptconverter.h"
#include <qvector.h>
#include "Models/dcinput.h"
#include "InputModels/diptvals.h"
class DCIptConverter : public AbstractDCIptConverter
{
public:
    DCIptConverter(AbstractDCInputBuilder *builder):
        AbstractDCIptConverter(builder){}
    DCInput convert(const DIptVals &input, const int &initRemScore, const DCPlayer &player) const override
    {
        DCInput ipt;
        if(input.point == -1 && input.score == -1)
            return iptBuilder()->create(initRemScore,player); // Create input model with default values
        return ipt =  copy(input); // Copy values from input to ipt
    }
    QVector<DCInput> convert(const QVector<DIptVals> &inputs) const override
    {
        QVector<DCInput> list;
        for (const auto &input : inputs)
            list << copy(input);
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
    DCInput copy(const DIptVals ipt) const
    {
        DCInput cIpt;
        cIpt.score = ipt.score;
        cIpt.point = ipt.point;
        cIpt.remScore = ipt.remainingScore;
        cIpt.roundIndex = ipt.roundIndex;
        cIpt.setIndex = ipt.setIndex;
        cIpt.attempt = ipt.attempt;
        cIpt.playerName = ipt.playerName;
        cIpt.min = ipt.min;
        cIpt.mid = ipt.mid;
        cIpt.max = ipt.max;
        cIpt.approved = ipt.approved;
        cIpt.inGame = ipt.inGame;
        return cIpt;
    }
};
#endif // DCIPTCONVERTER_H
