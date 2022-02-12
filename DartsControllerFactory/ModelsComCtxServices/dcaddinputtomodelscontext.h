#ifndef DCADDINPUTTOMODELSCONTEXT_H
#define DCADDINPUTTOMODELSCONTEXT_H
#include "DCInputSLAs/idcaddtomdsctx.h"
struct DCIndex;
struct DCPlayer;
struct DCMeta;
template<typename T> class IDCInputBuilder;
class IDCIndexConverter;
template<typename T,typename U> class IDCIndexController;
template<typename T,typename U> class IDCPlayerManager;
class IDCInputEvaluator;
template<typename T> class IDCMetaService;
class IDCByteArrayToInput;
class DCServices;
class QByteArray;
class DCAddInputToModelsContext : public IDCAddToMdsCtx
{
public:
    typedef IDCMetaService<DCMeta> MetaService;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCInputBuilder<DCInput> InputBuilder;
    DCAddInputToModelsContext(DCServices *services);
    DCInput add(const QByteArray &inputByteArray) override;
private:
    void updateModelsContext(DCInput &input);
    IDCByteArrayToInput *_byteArrayToInput;
    AbsDartsCtx *_modelsContext;
    MetaService *_metaService;
    IDCInputEvaluator *_inputEvaluator;
    PlayerManager *_playerManager;
    IndexController *_indexController;
    IDCIndexConverter *_indexToByteArray;
    InputBuilder *_inputToJson;
};
#endif // DCADDTOMODELCONTEXT_H
