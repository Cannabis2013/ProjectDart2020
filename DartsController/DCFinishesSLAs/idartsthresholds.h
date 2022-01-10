#ifndef IDARTSTHRESHOLDS_H
#define IDARTSTHRESHOLDS_H
class IDartsThresholds
{
public:
    virtual int terminalThreshold() const = 0;
    virtual int upperThresholdValue() const = 0;
};

#endif // IDARTSTHRESHOLDS_H
