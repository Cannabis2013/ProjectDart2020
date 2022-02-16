#ifndef DCREDOTURN_H
#define DCREDOTURN_H
#include "Routines/idcredoturn.h"
template<typename T> class IDCModelToJson;
template<typename T> class IDCInputConverter;
template<typename T> class IDCInputBuilder;
template<typename T> class IDCMetaManager;
template<typename T,typename U> class IDCPlayerManager;
template<typename T,typename U> class IDCIndexController;
class IDCIndexToByteArray;
class QJsonObject;
class IDCInputAdder;
struct DCPlayer;
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
    typedef IDCInputConverter<DCInput> ConvertInput;
    typedef IDCModelToJson<DCIndex> ConvertIndex;
    DCRedoTurn(DCServices *services);
    virtual QByteArray redo() override;
private:
    QJsonObject toJson(const QByteArray &byteArray);
    QByteArray toByteArray(const DCInput &input);
    QByteArray indexAsByteArray(const DCIndex &index);
    DCInput getInputFromModelsContext(const DCIndex &index);
    AbsDartsCtx *_modelsContext;
    IndexController *_indexController;
    PlayerManager *_playerManager;
    MetaManager *_metaManager;
    ConvertIndex *_indexToJson;
    CreateInput *_createInput;
    IDCInputAdder *_addInputDetails;
    ConvertInput *_convertInput;
};

#endif // DCREDOTURN_H
