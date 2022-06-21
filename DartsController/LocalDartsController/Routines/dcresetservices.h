#ifndef DCRESETSERVICES_H
#define DCRESETSERVICES_H

#include <DartsController/Contracts/Routines/idcresetservices.h>

class AbstractDartsContext;
template<typename T,typename U> class IDCPlayerManager;
struct DCInput;
struct DCPlayer;
template<typename T,typename U> class IDCIndexController;
struct DCMeta;
struct DCIndex;
template<typename T> class IDCMetaManager;
class DCServices;

class DCResetServices : public IDCResetServices
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCMetaManager<DCMeta> MetaManager;
    DCResetServices(DCServices *services);
    virtual bool reset() override;
private:
    MetaManager *_metaManager;
    IndexController *_indexController;
    PlayerManager *_playerManager;
    AbstractDartsContext *_modelsContext;
};

#endif // DCRESETSERVICES_H
