#ifndef DARTSINPUTSTATS_H
#define DARTSINPUTSTATS_H
#include "InputModelsSLAs/abstractdartsinput.h"
class DartsInputStats : public AbstractDartsInput
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
    double _middleVal = 0;
    int _minimum = 0;
    int _maximum = 0;
};

#endif // DARTSINPUTSTATS_H
