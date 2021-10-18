#ifndef DCAVERAGECALC_H
#define DCAVERAGECALC_H

#include "DartsController/DCInputStatsSLAs/idcaveragecalc.h"
#include <QRegExp>
#include <math.h>

class DCAverageCalc : public IDCAverageCalc
{
public:
    virtual double average(const DCInput &input, const IDCIndexService *indexService,
                           const IDCInitialScore *initialService) const override
    {

        auto initialScore = initialService->score();
        double totalScore =  initialScore - input.remainingScore;
        double attempts = indexService->roundIndex() * 3;
        double avg = totalScore / attempts;
        double roundedAverage = round(avg);
        return roundedAverage;
    }
private:
    double round(const double &value) const
    {
        auto stringNumber = QString::number(value);
        QRegExp reg("[0-9]+.[0-9]{2}");
        auto pos = reg.indexIn(stringNumber);
        if(pos != -1)
        {
            auto capturedText = reg.cap(0); // Ex.: c1c2,,,cn.d1d2
            auto lastCapturedDecimal = capturedText.at(capturedText.count() - 1);
            auto nextDecimal = getCharAt(stringNumber,capturedText.count());
            auto formattedDec = formatDecimal(lastCapturedDecimal,nextDecimal);
            capturedText.replace(capturedText.count() - 1,1,formattedDec);
            return capturedText.toDouble();
        }
        return -1;
    }
    QChar formatDecimal(const QChar &dec, const QChar &nextDec) const
    {
        auto d = toShort(dec);
        auto nD = toShort(nextDec);
        if(nD >= 5)
        {
            if(d == 9)
                return QChar(0);
            return QChar((d+49));
        }
        return dec;
    }
    short toShort(const QChar &c) const
    {
        return c.unicode() - 48;
    }
    QChar getCharAt(const QString &string, const int &pos) const
    {
        if(pos >= string.count())
            return QChar(48);
        else if(pos < 0)
            return QChar(48);
        return string.at(pos);
    }
};
#endif // DCAVERAGECALC_H
