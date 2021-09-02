#ifndef IDARTSCREATEINDEXES_H
#define IDARTSCREATEINDEXES_H


#include <qvector.h>
#include "idartspointindexes.h"
#include "idartsinput.h"
#include "itournament.h"
#include "isortinputmodels.h"
#include "icountinputmodels.h"
#include "igetinputmodelsservice.h"
#include "imodelsdbcontext.h"
template<typename TIndexes>
class IDartsCreateIndexes{
public:
    virtual const TIndexes* createIndexes(const IModel<QUuid> *tournament,
                                          const IGetInputModelsService *getInputsService,
                                          const ISortInputModels *sortInputsService,
                                          const ICountInputModels *countInputsService,
                                          const IModelsDbContext *dbService) const = 0;
};

#endif // IDARTSINDEXESBUILDER_H
