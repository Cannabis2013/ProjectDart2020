#ifndef CONTROLLERSLAS_H
#define CONTROLLERSLAS_H
#include "DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DartsController/DCIndexSLAs/dcindexslas.h"
#include "DartsController/DCScoresSLAs/dcplayerscoresslas.h"
#include "DartsController/ControllerSLA/abstractdartsctrl.h"
#include "DartsController/DCJsonSLAs/dcjsonslas.h"
#include "DartsController/DCMetaSLAs/dcmetaslas.h"
#include "DartsController/DCInputSLAs/dcinputsslas.h"
#include "DartsController/PlayerStatsSLAs/dcinputstatsslas.h"
class CtrlSLAs : public DCMetaSLAs,
                 public DCTurnvaluesSLAs,
                 public DCJsonSLAs,
                 public DCPlayerScoresSLAs,
                 public DCInputsSLAs,
                 public DCIndexSLAs,
                 public PlayerStatsSLAs
{};

#endif // CONTROLLERSLAS_H
