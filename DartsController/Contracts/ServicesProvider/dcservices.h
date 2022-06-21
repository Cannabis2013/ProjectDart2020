#ifndef DCSERVICES_H
#define DCSERVICES_H






class DCIndexServices;
class DCPlayersServices;
class DCInputsServices;
class DCFinishServices;
class DCMetaServices;
class AbstractDartsContext;

class DCServices
{
public:
    void setModelsContext(AbstractDartsContext *context) {_modelsContext = context;}
    AbstractDartsContext *modelsContext() const {return _modelsContext;}
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
    AbstractDartsContext *_modelsContext = nullptr;
    DCMetaServices *_metaServices;
    DCFinishServices *_finServices;
    DCPlayersServices *_playerServices;
    DCInputsServices *_inputServices;
    DCIndexServices *_indexServices;
};
#endif // DCSERVICES_H