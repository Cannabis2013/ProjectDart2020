#ifndef DCUNDOTURN_H
#define DCUNDOTURN_H
#include "Routines/idcundoturn.h"
template<typename T> class IDCInputConverter;
template<typename T> class IDCInputBuilder;
template<typename T> class IDCMetaManager;
template<typename T,typename U> class IDCPlayerManager;
template<typename T,typename U> class IDCIndexController;
class QJsonObject;
class IDCInputAdder;
class IDCIndexToByteArray;
struct DCPlayer;
struct DCInput;
struct DCMeta;
struct DCIndex;
class AbsDartsCtx;
class DCServices;
class DCUndoTurn : public IDCUndoTurn
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCMetaManager<DCMeta> MetaManager;
    typedef IDCInputBuilder<DCInput> CreateInput;
    typedef IDCInputConverter<DCInput> ConvertInput;
    DCUndoTurn(DCServices *services);
    virtual QByteArray undo() override;
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
    ConvertInput *_convertInput;
};

#endif // DCUNDOTURN_H
