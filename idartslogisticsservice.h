#ifndef ILOGISTICMANAGER_H
#define ILOGISTICMANAGER_H
template<class TString>
class IDartsLogisticsService
{
public:
    virtual TString suggestTargetRow(const int &remainingScore, const int &turnIndex) = 0;
};

#endif // ILOGISTICMANAGER_H
