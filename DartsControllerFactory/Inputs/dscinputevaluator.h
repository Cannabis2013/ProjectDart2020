#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "Inputs/idcinputevaluator.h"
struct DCIndex;
class DSCInputEvaluator : public IDCInputEvaluator
{
public:
    void evaluate(DCInput &input, DCMeta *meta, const DCPlayer &player) override;
private:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    void updateInputDetails(const int &scoreCand, DCInput &input, DCMeta *meta);
    void nullifyInput(DCInput &input, DCMeta *meta);
    void updateWinnerDetails(DCInput &input, DCMeta *meta);
    int calcScore(const int &scoreCand, const int &remScore);
    void update(const int &scoreCand, DCInput &input, DCMeta *meta);
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
