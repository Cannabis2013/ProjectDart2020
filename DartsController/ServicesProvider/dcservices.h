#ifndef DCSERVICES_H
#define DCSERVICES_H
#include "Routines/dcroutines.h"
#include "DCTurnValuesSLAs/dcturnvaluesservices.h"
#include "DCIndexSLAs/dcindexservices.h"
#include "DCScoresSLAs/dcplayersservices.h"
#include "DCJsonSLAs/dcjsonservices.h"
#include "DCMetaSLAs/dcmetaservices.h"
#include "DCInputSLAs/dcinputsservices.h"
#include "DCFinishesSLAs/dcfinishesservices.h"
class DCServices
{
public:
    void setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
    AbsDartsCtx *modelsContext() {return _modelsContext;}
    DCMetaServices *metaServices() const {return _metaServices;}
    void setMetaServices(DCMetaServices *services) {_metaServices = services;}
    DCFinishServices *finServices() const {return _finServices;}
    void setFinServices(DCFinishServices *services) {_finServices = services;}
    DCTurnValuesServices *turnValsServices() const {return _turnValsServices;}
    void setTurnValsServices(DCTurnValuesServices *services) {_turnValsServices = services;}
    DCJsonServices *jsonServices() const {return _jsonServices;}
    void setJsonServices(DCJsonServices *services) {_jsonServices = services;}
    DCInputsServices *inputServices() const {return _inputServices;}
    void setInputServices(DCInputsServices *services) {_inputServices = services;}
    DCPlayersServices *playerServices() const {return _playerServices;}
    void setPlayerServices(DCPlayersServices *services) {_playerServices = services;}
    DCIndexServices *indexServices() const {return _indexServices;}
    void setIndexServices(DCIndexServices *services) {_indexServices = services;}
    DCRoutines *routines() const {return _routines;}
    void setRoutines(DCRoutines *services) {_routines = services;}
private:
    AbsDartsCtx *_modelsContext = nullptr;
    DCMetaServices *_metaServices;
    DCFinishServices *_finServices;
    DCTurnValuesServices *_turnValsServices;
    DCJsonServices *_jsonServices;
    DCPlayersServices *_playerServices;
    DCInputsServices *_inputServices;
    DCIndexServices *_indexServices;
    DCRoutines *_routines;
};
#endif // DCSERVICES_H
