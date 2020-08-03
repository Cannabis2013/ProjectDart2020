#ifndef ILOGISTICMANAGER_H
#define ILOGISTICMANAGER_H
template<class TString>
class IPointLogisticInterface
{
public:
    virtual TString constructThrowSuggestions(const int &remainingScore,const int &turnIndex) = 0;
    virtual void setNumberOfThrows(const int &throwCount) = 0;
    virtual void setAcceptedEndGameModifier(const int &keyCode) = 0;
    virtual int acceptedEndGameModifier() = 0;
private:
};

#endif // ILOGISTICMANAGER_H
