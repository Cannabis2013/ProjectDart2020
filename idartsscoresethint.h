#ifndef IDARTSSCORESETHINT_H
#define IDARTSSCORESETHINT_H
#include "idartsscoreinput.h"
#include "idartsscoreindexes.h"
template<typename TDbModelsService>
class IDartsScoreSetHint
{
public:
    virtual void setDartsScoreHint(const IModel<QUuid>* model,const int &hint, TDbModelsService* dbService) = 0 ;
};
#endif // IDARTSSCOREMODELSSERVICE_H
