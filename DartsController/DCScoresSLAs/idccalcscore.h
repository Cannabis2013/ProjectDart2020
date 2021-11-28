#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H
#include "abstractdcscoresctx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
#include "DartsController/DCInputSLAs/dciptvals.h"
class IDCCalcScore
{
public:
    virtual int calc(DCIptVals &input) const = 0;
    virtual int calc(const DCIndex &index, const int &scoreCandidate, AbstractDCScoresCtx *scoresService) const = 0;
};
#endif // IDCCALCSCORE_H
