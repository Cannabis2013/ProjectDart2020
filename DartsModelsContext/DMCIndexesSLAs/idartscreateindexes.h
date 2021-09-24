#ifndef IDARTSCREATEINDEXES_H
#define IDARTSCREATEINDEXES_H


#include <qvector.h>
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "DartsModelsContext/DMCInputSLAs/isortinputmodels.h"
#include "DartsModelsContext/DMCInputSLAs/icountinputmodels.h"
#include "DartsModelsContext/DMCInputSLAs/igetinputmodelsservice.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
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
