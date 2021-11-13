#ifndef DSCCALCMIDVAL_H
#define DSCCALCMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idccalcmidval.h"
#include <QRegExp>
class DSCCalcMidVal : public IDCCalcMidVal
{
public:
    virtual double middleValue(IDartsIndex *index, const int &remainingScore, const int &initialScore) const override
    {
        auto scoresAccumulated = initialScore - remainingScore;
        auto roundIndex = index->roundIndex();
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
