#ifndef IDARTSTHRESHOLDVALUES_H
#define IDARTSTHRESHOLDVALUES_H

class IDartsThresholdValues
{
public:
    virtual int upperThresholdValue() const = 0;
    virtual int terminalThreshold() const = 0;
};
#endif // IDARTSTHRESHOLDVALUES_H
