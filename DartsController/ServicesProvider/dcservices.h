#ifndef DCSERVICES_H
#define DCSERVICES_H
#include "Routines/dartscontrollerroutines.h"
#include "Index/dcindexservices.h"
#include "Players/dcplayersservices.h"
#include "Meta/dcmetaservices.h"
#include "Inputs/dcinputsservices.h"
#include "Finishes/dcfinishesservices.h"
class DCServices
{
public:
    void setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
    AbsDartsCtx *modelsContext() {return _modelsContext;}
    DCMetaServices *metaServices() const {return _metaServices;}
    void setMetaServices(DCMetaServices *services) {_metaServices = services;}
    DCFinishServices *finServices() const {return _finServices;}
    void setFinServices(DCFinishServices *services) {_finServices = services;}
    DCInputsServices *inputServices() const {return _inputServices;}
    void setInputServices(DCInputsServices *services) {_inputServices = services;}
    DCPlayersServices *playerServices() const {return _playerServices;}
    void setPlayerServices(DCPlayersServices *services) {_playerServices = services;}
    DCIndexServices *indexServices() const {return _indexServices;}
    void setIndexServices(DCIndexServices *services) {_indexServices = services;}
private:
    AbsDartsCtx *_modelsContext = nullptr;
    DCMetaServices *_metaServices;
    DCFinishServices *_finServices;
    DCPlayersServices *_playerServices;
    DCInputsServices *_inputServices;
    DCIndexServices *_indexServices;
};
#endif // DCSERVICES_H
