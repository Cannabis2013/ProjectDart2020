#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H
#include "idcscoremodels.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class IDCCalcScore
{
public:
    virtual int calculate(AbstractDartsInput *input) const = 0;
    virtual int calculate(IDartsIndex *index, const int &scoreCandidate, IDCScoreModels *scoresService) const = 0;
};
#endif // IDCCALCSCORE_H
