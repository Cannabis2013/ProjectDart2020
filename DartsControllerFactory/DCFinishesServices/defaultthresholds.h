#ifndef DEFAULTTHRESHOLDS_H
#define DEFAULTTHRESHOLDS_H
#include "DCFinishesSLAs/idartsthresholds.h"
class DefaultThresholds : public IDartsThresholds
{
    // IDartsThresholds interface
public:
    virtual int terminalThreshold() const override;
    virtual int upperThresholdValue() const override;
};

#endif // DARTSTHRESHOLDS_H
