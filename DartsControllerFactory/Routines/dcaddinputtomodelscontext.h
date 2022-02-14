#ifndef DCADDINPUTTOMODELSCONTEXT_H
#define DCADDINPUTTOMODELSCONTEXT_H
#include "Routines/idcaddtomdsctx.h"

class IDCInputAdder;
template<typename T> class IDCInputConverter;
template<typename T,typename U> class IDCIndexController;
template<typename T,typename U> class IDCPlayerManager;
template<typename T> class IDCMetaManager;
class QJsonObject;
struct DCIndex;
struct DCPlayer;
struct DCMeta;
class IDCIndexToByteArray;
class IDCInputEvaluator;
class DCServices;
class QByteArray;
class DCAddInputToModelsContext : public IDCAddToMdsCtx
{
public:
    typedef IDCMetaManager<DCMeta> MetaService;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCInputConverter<DCInput> ConvertInput;
    DCAddInputToModelsContext(DCServices *services);
    QByteArray add(const QByteArray &inputByteArray) override;
private:
    DCInput toInputModel(const QByteArray &byteArray);
    void updateModelsContext(DCInput &input);
    QByteArray inputToByteArray(const DCInput &input);
    AbsDartsCtx *_modelsContext;
    MetaService *_metaManager;
    IDCInputEvaluator *_inputEvaluator;
    PlayerManager *_playerManager;
    IndexController *_indexController;
    IDCIndexToByteArray *_indexToByteArray;
    ConvertInput *_convertInput;
    IDCInputAdder *_addInputDetails;
};
#endif // DCADDTOMODELCONTEXT_H
