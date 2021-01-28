#ifndef ILOGISTICMANAGER_H
#define ILOGISTICMANAGER_H
template<class TString>
class FTPLogisticControllerInterface
{
public:
    virtual TString suggestTargetRow(const int &remainingScore, const int &turnIndex) = 0;
};

#endif // ILOGISTICMANAGER_H
