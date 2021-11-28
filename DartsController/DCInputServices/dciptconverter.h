#ifndef DCIPTCONVERTER_H
#define DCIPTCONVERTER_H
#include "DartsController/DCInputSLAs/idciptconverter.h"
#include <qvector.h>
class DCIptConverter : public IDCIptConverter
{
public:
    DCIptVals convert(AbstractDartsInput *input) const override
    {
        return create(input);
    }
    QVector<DCIptVals> convert(const QVector<AbstractDartsInput *> &inputs) const override
    {
        QVector<DCIptVals> list;
        for (const auto &input : inputs)
            list << create(input);
        return list;
    }
    DIptVals convert(DCIptVals &input) const override
    {
        DIptVals iptVals;
        iptVals.score = input.score;
        iptVals.point = input.point;
        iptVals.roundIndex = input.roundIndex;
        iptVals.setIndex = input.setIndex;
        iptVals.attempt = input.attempt;
        iptVals.playerId = input.playerId;
        iptVals.playerName = input.playerName;
        iptVals.min = input.min;
        iptVals.mid = input.mid;
        iptVals.max = input.max;
        iptVals.approved = input.approved;
        iptVals.inGame = input.inGame;
        return iptVals;
    }
private:
    DCIptVals create(AbstractDartsInput *ipt) const
    {
        DCIptVals cIpt;
        cIpt.score = ipt->score();
        cIpt.point = ipt->point();
        cIpt.roundIndex = ipt->roundIndex();
        cIpt.setIndex = ipt->setIndex();
        cIpt.attempt = ipt->attempt();
        cIpt.playerId = ipt->playerId();
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
