#ifndef CONTROLLERSLAS_H
#define CONTROLLERSLAS_H
#include "DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DCIndexSLAs/dcindexslas.h"
#include "DCScoresSLAs/dcplayerscoresslas.h"
#include "DCJsonSLAs/dcjsonslas.h"
#include "DCMetaSLAs/dcmetaslas.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
class CtrlSLAs : public DCMetaSLAs,
                 public DCTurnvaluesSLAs,
                 public DCJsonSLAs,
                 public DCPlayerScoresSLAs,
                 public DCInputsSLAs,
                 public DCIndexSLAs,
                 public PlayerStatsSLAs
{};

#endif // CONTROLLERSLAS_H
