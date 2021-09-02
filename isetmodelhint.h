#ifndef ISETMODELHINT_H
#define ISETMODELHINT_H
#include "idartsinput.h"
template<typename TDbModelsService>
class ISetModelHint
{
public:
    virtual void setHint(const IModel<QUuid>* model,const int &hint, TDbModelsService* dbService) = 0 ;
};
#endif // IDARTSSCOREMODELSSERVICE_H
