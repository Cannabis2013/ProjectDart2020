#ifndef DCADDINPUT_H
#define DCADDINPUT_H
#include "Routines/idcaddinput.h"

template<typename T> class IDCInputConverter;
template<typename T> class IDCModelToJson;
template<typename T,typename U> class IDCIndexController;
template<typename T,typename U> class IDCPlayerManager;
template<typename T> class IDCMetaManager;
class IDCInputAdder;
class QJsonObject;
struct DCIndex;
struct DCPlayer;
struct DCMeta;
class IDCIndexToByteArray;
class IDCInputEvaluator;
class DCServices;
class QByteArray;
class DCAddInput : public IDCAddInput
{
public:
    typedef IDCMetaManager<DCMeta> MetaService;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCInputConverter<DCInput> ConvertInput;
    typedef IDCModelToJson<DCIndex> ConvertIndex;
    DCAddInput(DCServices *services);
    QByteArray add(const QByteArray &inputByteArray) override;
private:
    DCInput convertToInput(const QByteArray &byteArray);
    void evaluate(DCInput &input);
    void updateModelsContext(DCInput &input);
    void updateControllerContext(DCInput &input);
    QByteArray inputToByteArray(const DCInput &input);
    QByteArray indexToByteArray(const DCIndex &index);
    AbsDartsCtx *_modelsContext;
    MetaService *_metaManager;
    IDCInputEvaluator *_inputEvaluator;
    PlayerManager *_playerManager;
    IndexController *_indexController;
    ConvertIndex *_indexToByteArray;
    ConvertInput *_convertInput;
    IDCInputAdder *_addInputDetails;
};
#endif // DCADDTOMODELCONTEXT_H
