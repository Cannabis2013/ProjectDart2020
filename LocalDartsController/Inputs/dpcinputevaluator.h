#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H

#include <DartsController/Inputs/idcinputevaluator.h>

class DPCInputEvaluator : public IDCInputEvaluator
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
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    void playerHasNotEntered(DCInput &ipt, const int &scoreCand, DCMeta *meta);
    void playerHasEntered(DCInput &ipt, DCMeta *meta, const int &scoreCand);
    void updateWinnerDetails(DCInput &ipt, DCMeta *meta);
    int calcScore(const int &scoreCand, const int &remScore);
    void updateInputDetails(const int &remaining, const bool &inGame, DCInput &input, DCMeta *meta);
    void nullifyInput(DCInput &input, DCMeta *meta);
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
