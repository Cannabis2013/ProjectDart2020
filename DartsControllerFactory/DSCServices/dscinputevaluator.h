#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DCInputSLAs/idcipteval.h"
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"
#include "ServicesProvider/dcservices.h"
class DSCInputEvaluator : public IDCIptEval
{
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    DSCInputEvaluator(DCServices *services);
    void eval(DCInput &input) override;
private:
    int calcScore(const int &scoreCand, const int &remScore);
    void update(const int &scoreCand, DCInput &input, DCMeta *meta);
    const int minimumAllowedScore = 2;
    DCServices *_services;
};
#endif // SCOREVALIDATOR_H
