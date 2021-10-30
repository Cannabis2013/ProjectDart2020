#ifndef DPCCALCMIDVAL_H
#define DPCCALCMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idccalcmidval.h"
#include <qregexp.h>
#include <qstring.h>
class DPCCalcMidVal : public IDCCalcMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const override
    {
        auto scoresAccumulated = initialScore - remainingScore;
        auto divisor = index.roundIndex*3 + index.attemptIndex - 2;
        auto mid = (double)scoresAccumulated/divisor;
        return toTwoDecimals(mid);
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

#endif // DPCCALCMIDVAL_H
