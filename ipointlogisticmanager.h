#ifndef ILOGISTICMANAGER_H
#define ILOGISTICMANAGER_H
template<class TString>
class IPointLogisticManager
{
public:
    virtual TString constructThrowSuggestions(const int &remainingScore,const int &turnIndex) = 0;

private:
};

#endif // ILOGISTICMANAGER_H
