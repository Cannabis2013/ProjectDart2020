#ifndef IDCADDSCORE_H
#define IDCADDSCORE_H

#include <idcmodel.h>
#include <idcscoresservice.h>
#include <quuid.h>
class IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCContext::IDCModel *model, IDCScoresService *scoresService) const = 0;
};

#endif // IDARTSADDSCORE_H
