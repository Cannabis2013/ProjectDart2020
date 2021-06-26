#ifndef IDARTSINPUTSUGGESTION_H
#define IDARTSINPUTSUGGESTION_H
template<class TString>
class IDartsInputSuggestion
{
public:
    virtual TString suggestTargetRow(const int &remainingScore, const int &turnIndex) const = 0;
};

#endif // ILOGISTICMANAGER_H
