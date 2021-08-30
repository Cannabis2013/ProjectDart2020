#ifndef IDARTSSUBTRACTSCORES_H
#define IDARTSSUBTRACTSCORES_H

#include <idcscoresservice.h>
#include <idscmodel.h>

class IDartsSubtractScore
{
public:
    virtual int subtractPlayerScore(const DSCContext::IDSCModel *model, IDCScoresService *scoresService) = 0;
    virtual void subtractPlayerScore(const QVector<DSCContext::IDSCModel*> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
