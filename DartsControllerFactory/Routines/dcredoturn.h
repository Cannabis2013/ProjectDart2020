#ifndef DCREDOTURN_H
#define DCREDOTURN_H
#include "Routines/idcredoturn.h"
class QJsonObject;
class IDCInputAdder;
template<typename T> class IDCInputBuilder;
class IDCIndexToByteArray;
template<typename T> class IDCMetaManager;
template<typename T,typename U> class IDCPlayerManager;
struct DCPlayer;
template<typename T,typename U> class IDCIndexController;
struct DCInput;
struct DCMeta;
struct DCIndex;
class AbsDartsCtx;
class DCServices;
class DCRedoTurn : public IDCRedoTurn
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCMetaManager<DCMeta> MetaManager;
    typedef IDCInputBuilder<DCInput> CreateInput;
    DCRedoTurn(DCServices *services);
    virtual QByteArray redo() override;
private:
    QJsonObject toJson(const QByteArray &byteArray);
    QByteArray toByteArray(const DCInput &input);
    DCInput getInputFromModelsContext(const DCIndex &index);
    AbsDartsCtx *_modelsContext;
    IndexController *_indexController;
    PlayerManager *_playerManager;
    MetaManager *_metaManager;
    IDCIndexToByteArray *_indexToByteArray;
    CreateInput *_createInput;
    IDCInputAdder *_addInputDetails;
};

#endif // DCREDOTURN_H
