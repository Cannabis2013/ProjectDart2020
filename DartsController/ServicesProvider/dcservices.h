#ifndef DCSERVICES_H
#define DCSERVICES_H
#include "RoutineServices/dcroutines.h"
#include "DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DCIndexSLAs/dcindexslas.h"
#include "DCScoresSLAs/dcplayersslas.h"
#include "DCJsonSLAs/dcjsonslas.h"
#include "DCMetaSLAs/dcmetaslas.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "DCFinishesSLAs/dcfinishesservices.h"
#include "InitSLAs/dcinitservices.h"
class DCServices : public DCMetaSLAs,
                   public DCFinishesSLAs,
                   public DCTurnvaluesSLAs,
                   public DCJsonSLAs,
                   public DCPlayersSLAs,
                   public DCInputsSLAs,
                   public DCIndexSLAs,
                   public PlayerStatsSLAs,
                   public DCInitServices,
                   public DCRoutines
{
public:
    void setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
    AbsDartsCtx *mdsCtx() {return _modelsContext;}
protected:
    void updateServices(const DCInput &ipt);
private:
    AbsDartsCtx *_modelsContext = nullptr;
};

#endif // DCSERVICES_H
