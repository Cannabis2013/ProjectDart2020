#ifndef ICREATEDARTSINDEXES_H
#define ICREATEDARTSINDEXES_H


#include <qvector.h>
#include "idartspointindexes.h"
#include "idartspointinput.h"
#include "itournament.h"
#include "isortinputmodels.h"
#include "icountinputmodels.h"
#include "igetinputmodelsservice.h"
#include "idartsinputdb.h"
namespace DartsModelsContext{
    template<typename TIndexes>
    class ICreateDartsIndexes{
    public:
        virtual const TIndexes* createIndexes(const ITournament *tournament,
                                              const IGetInputModelsService *getInputsService,
                                              const ISortInputModels *sortInputsService,
                                              const ICountInputModels *countInputsService,
                                              const IDartsInputDb *dbService) const = 0;
    };
}

#endif // IDARTSINDEXESBUILDER_H
