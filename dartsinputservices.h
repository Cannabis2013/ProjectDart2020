#ifndef DARTSINPUTSERVICES_H
#define DARTSINPUTSERVICES_H

#include <icountinputmodels.h>
#include <icreatejsonfromdartspointindexes.h>
#include <idartscreateindexes.h>
#include <idartscreatejsonfromscoreindexes.h>
#include <idartscreatejsonfromscores.h>
#include <idartsmodelscreatejsonfrompoints.h>
#include <idartspointindexes.h>
#include <idartspointsethint.h>
#include <idartsscoreindexes.h>
#include <idartsscoresethint.h>
#include <igetdartspointfromdb.h>
#include <igetdartsscorefromdb.h>
#include <igetinputmodelsservice.h>
#include "iremovedartsinputsfromdb.h"
#include <isortinputmodels.h>
#include "idartscreateinput.h"
#include "idartscreatejsonfrommodel.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"

class DartsInputServices
{
public:
    typedef IPredicate<IPlayerInput> Predicate;
    typedef IDartsScoreSetHint<IDartsInputDb> ScoreModelsService;
    typedef IModelsDbContext<IPlayerInput> DbService;
    IDartsModelsCreateJsonFromPoints *dartsPointsJsonService() const;
    void setDartsPointsJsonService(IDartsModelsCreateJsonFromPoints *newDartsPointsJsonService);
    IDartsCreateJsonFromScores *createJsonFromScoreModels() const;
    void setCreateJsonFromScoreModels(IDartsCreateJsonFromScores *newCreateJsonFromScoreModels);
    IDartsPointSetHint *dartsPointSetHint() const;
    void setDartsPointSetHint(IDartsPointSetHint *newDartsPointSetHint);
    ISortInputModels *sortInputs() const;
    void setSortInputs(ISortInputModels *newSortInputs);
    ScoreModelsService *dartsScoreSetHint() const;
    void setDartsScoreSetHint(ScoreModelsService *newDartsScoreSetHint);
    IGetInputModelsService *getInputsFromDb() const;
    void setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb);
    ICountInputModels *countInputs() const;
    void setCountInputs(ICountInputModels *newCountInputs);
    Predicate *sortPointInputsByIndexes() const;
    void setSortPointInputsByIndexes(Predicate *newSortPointInputsByIndexes);
    Predicate *sortScoreInputsByIndexes() const;
    void setSortScoreInputsByIndexes(Predicate *newSortScoreInputsByIndexes);
    IGetDartsScoreFromDb *getScoreFromDb() const;
    void setGetScoreFromDb(IGetDartsScoreFromDb *newGetScoreFromDb);
    IGetDartsPointFromDb *getPointFromDb() const;
    void setGetPointFromDb(IGetDartsPointFromDb *newGetPointFromDb);
    ICreateJsonfromDartsPointIndexes *createJsonFromPointIndexes() const;
    void setCreateJsonFromPointIndexes(ICreateJsonfromDartsPointIndexes *newCreateJsonFromPointIndexes);
    IDartsCreateJsonFromScoreIndexes *createJsonfromScoreIndexes() const;
    void setCreateJsonfromScoreIndexes(IDartsCreateJsonFromScoreIndexes *newCreateJsonfromScoreIndexes);
    IDartsInputDb *dartsPointsDb() const;
    void setDartsPointsDb(IDartsInputDb *newDartsPointsDb);
    IDartsInputDb *dartsScoresDb() const;
    void setDartsScoresDb(IDartsInputDb *newDartsScoresDb);
    IDartsCreateInput *createScoreModel() const;
    void setCreateScoreModel(IDartsCreateInput *newCreateScoreModel);
    IDartsCreateInput *createPointModel() const;
    void setCreatePointModel(IDartsCreateInput *newCreatePointModel);
    IDartsCreateJsonFromModel<IPlayerInput> *createJsonFromDartsPoint() const;
    void setCreateJsonFromDartsPoint(IDartsCreateJsonFromModel<IPlayerInput> *newCreateJsonFromDartsPoint);
    IDartsCreateJsonFromModel<IPlayerInput> *createJsonFromDartsScore() const;
    void setCreateJsonFromDartsScore(IDartsCreateJsonFromModel<IPlayerInput> *newCreateJsonFromDartsScore);
    IRemoveDartsInputsFromDb *removeInputsFromDb() const;
    void setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService);
    IDartsCreateIndexes<IDartsScoreIndexes> *createIndexesFromScoreModels() const;
    void setCreateIndexesFromScoreModels(IDartsCreateIndexes<IDartsScoreIndexes> *newCreateIndexesFromScoreModels);
    IDartsCreateIndexes<IDartsPointIndexes> *createIndexesFromPointModels() const;
    void setCreateIndexesFromPointModels(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels);
private:
    IDartsModelsCreateJsonFromPoints* _dartsPointsJsonService;
    IDartsCreateJsonFromScores* _createJsonFromScoreModels;
    IDartsPointSetHint *_dartsPointSetHint;
    ISortInputModels* _sortInputs;
    ScoreModelsService *_dartsScoreSetHint;
    IGetInputModelsService* _getInputsFromDb;
    ICountInputModels* _countInputs;
    Predicate* _sortPointInputsByIndexes;
    Predicate *_sortScoreInputsByIndexes;
    IGetDartsScoreFromDb *_getScoreFromDb;
    IGetDartsPointFromDb *_getPointFromDb;
    ICreateJsonfromDartsPointIndexes *_createJsonFromPointIndexes;
    IDartsCreateJsonFromScoreIndexes *_createJsonfromScoreIndexes;
    IRemoveDartsInputsFromDb* _removeDartsInputsFromDb;
    IDartsCreateInput *_createPointModel;
    IDartsCreateInput *_createScoreModel;
    IDartsCreateJsonFromModel<IPlayerInput> *_createJsonFromDartsPoint;
    IDartsCreateJsonFromModel<IPlayerInput> *_createJsonFromDartsScore;
    IDartsCreateIndexes<IDartsScoreIndexes> *_createIndexesFromScoreModels;
    IDartsCreateIndexes<IDartsPointIndexes> *_createIndexesFromPointModels;
    IDartsInputDb *_dartsPointsDb;
    IDartsInputDb *_dartsScoresDb;
};

#endif // DARTSINPUTSERVICES_H
