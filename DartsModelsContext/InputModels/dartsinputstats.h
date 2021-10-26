#ifndef DARTSINPUTSTATS_H
#define DARTSINPUTSTATS_H
#include "DartsModelsContext/InputModelsSLAs/idartsinputstats.h"
class DartsInputStats : public IDartsInputStats
{
public:
    virtual double middleValue() const override
    {
        return _middleVal;
    }
    virtual void setMiddleValue(const double &midVal) override
    {
        _middleVal = midVal;
    }
    virtual int currentMaximum() const override
    {
        return _maximum;
    }
    virtual void setCurrentMaximum(const int &max) override
    {
        _maximum = max;
    }
    virtual int currentMinimum() const override
    {
        return _minimum;
    }
    virtual void setCurrentMinimum(const int &min) override
    {
        _minimum = min;
    }
private:
    double _middleVal;
    int _minimum;
    int _maximum;
};

#endif // DARTSINPUTSTATS_H
