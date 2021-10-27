#ifndef DSCCALCMIDVAL_H
#define DSCCALCMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idcupdatemidval.h"
class DSCCalcMidVal : public IDCUpdateMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const IDCInitialScore *initialScore) const override
    {
        auto initial = initialScore->score();
        auto scoresAccumulated = initial - remainingScore;
        auto roundIndex = index.roundIndex;
        auto midVal = (double)scoresAccumulated/roundIndex;
        return toTwoDecimals(midVal);
    }
private:
    double toTwoDecimals(const double &value) const
    {
        auto stringVal = QString::number(value);
        QRegExp reg("\\d+.\\d{2}");
        auto pos = reg.indexIn(stringVal);
        if(pos == -1)
            return stringVal.toDouble();
        return reg.cap(0).toDouble();
    }
};
#endif // DSCCALCMIDDLEVAL_H
