#ifndef DARTSINPUTSERVICES_H
#define DARTSINPUTSERVICES_H

#include <icountinputmodels.h>
#include <icreatejsonfromdartspointindexes.h>
#include <idartscreateindexes.h>
#include <idartsmodelscreatejsonfrompoints.h>
#include <idartspointindexes.h>
#include <idartspointsethint.h>
#include <isetmodelhint.h>
#include <igetdartspointfromdb.h>
#include <igetinputmodelsservice.h>
#include "iremovedartsinputsfromdb.h"
#include <isortinputmodels.h>
#include "idartscreateinput.h"
#include "idartscreatejsonfrommodel.h"
#include "idartsinput.h"
#include "idartsinput.h"

class DartsInputServices
{
public:
    typedef IPredicate<IModel<QUuid>> Predicate;
    typedef IDbContext<IPlayerInput> DbService;
    IDartsModelsCreateJsonFromPoints *dartsPointsJsonService() const;
    void setDartsPointsJsonService(IDartsModelsCreateJsonFromPoints *newDartsPointsJsonService);
    IDartsPointSetHint *dartsPointSetHint() const;
    void setDartsPointSetHint(IDartsPointSetHint *newDartsPointSetHint);
    ISortInputModels *sortInputs() const;
    void setSortInputs(ISortInputModels *newSortInputs);
    IGetInputModelsService *getInputsFromDb() const;
    void setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb);
    ICountInputModels *countInputs() const;
    void setCountInputs(ICountInputModels *newCountInputs);
    Predicate *sortPointInputsByIndexes() const;
    void setSortPointInputsByIndexes(Predicate *newSortPointInputsByIndexes);
    IGetDartsPointFromDb *getPointFromDb() const;
    void setGetPointFromDb(IGetDartsPointFromDb *newGetPointFromDb);
    ICreateJsonfromDartsPointIndexes *createJsonFromPointIndexes() const;
    void setCreateJsonFromPointIndexes(ICreateJsonfromDartsPointIndexes *newCreateJsonFromPointIndexes);
    IModelsDbContext *inputsDb() const;
    void setInputsDb(IModelsDbContext *newDartsPointsDb);
    IDartsCreateInput *createPointModel() const;
    void setCreatePointModel(IDartsCreateInput *newCreatePointModel);
    IDartsCreateJsonFromModel<IModel<QUuid> > *createJsonFromDartsPoint() const;
    void setCreateJsonFromDartsPoint(IDartsCreateJsonFromModel<IModel<QUuid> > *newCreateJsonFromDartsPoint);
    IRemoveDartsInputsFromDb *removeInputsFromDb() const;
    void setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService);
    IDartsCreateIndexes<IDartsPointIndexes> *createControllerIndexes() const;
    void setCreateIndexesFromPointModels(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels);
private:
    IDartsModelsCreateJsonFromPoints* _dartsPointsJsonService;
    IDartsPointSetHint *_dartsPointSetHint;
    ISortInputModels* _sortInputs;
    IGetInputModelsService* _getInputsFromDb;
    ICountInputModels* _countInputs;
    Predicate* _sortPointInputsByIndexes;
    IGetDartsPointFromDb *_getPointFromDb;
    ICreateJsonfromDartsPointIndexes *_createJsonFromPointIndexes;
    IRemoveDartsInputsFromDb* _removeDartsInputsFromDb;
    IDartsCreateInput *_createPointModel;
    IDartsCreateJsonFromModel<IModel<QUuid>> *_createJsonFromDartsPoint;
    IDartsCreateIndexes<IDartsPointIndexes> *_createIndexesFromPointModels;
    IModelsDbContext *_inputsDb;
};

#endif // DARTSINPUTSERVICES_H
