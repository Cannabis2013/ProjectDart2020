#ifndef IDARTSINPUTSTATS_H
#define IDARTSINPUTSTATS_H

class IDartsInputStats
{
public:
    virtual double middleValue() const = 0;
    virtual void setMiddleValue(const double &avg) = 0;
    virtual int currentMaximum() const = 0;
    virtual void setCurrentMaximum(const int &max) = 0;
    virtual int currentMinimum() const = 0;
    virtual void setCurrentMinimum(const int &min) = 0;
};

#endif // IDARTSINPUTSTATS_H
