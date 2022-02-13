#ifndef DCADDINPUTTOMODELSCONTEXT_H
#define DCADDINPUTTOMODELSCONTEXT_H
#include "Routines/idcaddtomdsctx.h"
struct DCIndex;
struct DCPlayer;
struct DCMeta;
template<typename T> class IDCInputBuilder;
class IDCIndexToByteArray;
template<typename T,typename U> class IDCIndexController;
template<typename T,typename U> class IDCPlayerManager;
class IDCInputEvaluator;
template<typename T> class IDCMetaManager;
class DCServices;
class QByteArray;
class DCAddInputToModelsContext : public IDCAddToMdsCtx
{
public:
    typedef IDCMetaManager<DCMeta> MetaService;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCInputBuilder<DCInput> InputBuilder;
    DCAddInputToModelsContext(DCServices *services);
    DCInput add(const QByteArray &inputByteArray) override;
private:
    DCInput toInputModel(const QByteArray &byteArray);
    void updateModelsContext(DCInput &input);
    AbsDartsCtx *_modelsContext;
    MetaService *_metaService;
    IDCInputEvaluator *_inputEvaluator;
    PlayerManager *_playerManager;
    IndexController *_indexController;
    IDCIndexToByteArray *_indexToByteArray;
    InputBuilder *_inputConverter;
};
#endif // DCADDTOMODELCONTEXT_H
