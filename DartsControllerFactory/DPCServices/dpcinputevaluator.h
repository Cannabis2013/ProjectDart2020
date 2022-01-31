#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DCInputSLAs/idcipteval.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"

#include "ServicesProvider/dcservices.h"
class DPCInputEvaluator : public IDCIptEval
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
    void eval(DCInput &input) override;
private:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    void playerHasNotEntered(DCInput &ipt, const int &scoreCand);
    void playerHasEntered(DCInput &ipt, DCMeta *meta,const int &scoreCand);
    void setWinnerValues(DCInput &ipt, DCMeta *meta);
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
    DCServices *_services;
};
#endif // POINTVALIDATOR_H
