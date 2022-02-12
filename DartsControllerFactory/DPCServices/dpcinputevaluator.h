#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DCInputSLAs/idcinputevaluator.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"

#include "ServicesProvider/dcservices.h"
class DPCInputEvaluator : public IDCInputEvaluator
{
    Q_OBJECT
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    DPCInputEvaluator(DCServices *services);
    void evaluate(DCInput &input) override;
private:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    void playerHasNotEntered(DCInput &ipt, const int &scoreCand);
    void playerHasEntered(DCInput &ipt, DCMeta *meta,const int &scoreCand);
    void setWinnerValues(DCInput &ipt, DCMeta *meta);
    int calcScore(const int &scoreCand, const int &remScore);
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
    DCServices *_services;
};
#endif // POINTVALIDATOR_H
