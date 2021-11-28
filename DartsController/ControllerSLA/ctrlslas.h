#ifndef CONTROLLERSLAS_H
#define CONTROLLERSLAS_H
#include "DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DartsController/DCIndexSLAs/dcindexslas.h"
#include "DartsController/DCScoresSLAs/dcscoreslas.h"
#include "DartsController/DCPlayerSLAs/DCPlayerSLAs.h"
#include "DartsController/ControllerSLA/abstractdartsctrl.h"
#include "DartsController/DCJsonSLAs/dcjsonslas.h"
#include "DartsController/DCMetaSLAs/dcmetaslas.h"
#include "DartsController/DCInputSLAs/dcinputsslas.h"
#include "DartsController/PlayerStatsSLAs/dcinputstatsslas.h"
class CtrlSLAs : public DCMetaSLAs,
                       public DCTurnvaluesSLAs,
                       public DCJsonSLAs,
                       public DCScoreSLAs,
                       public DCPlayerSLAs,
                       public DCInputsSLAs,
                       public DCIndexSLAs,
                       public PlayerStatsSLAs
{};

#endif // CONTROLLERSLAS_H
