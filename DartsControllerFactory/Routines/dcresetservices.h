#ifndef DCRESETSERVICES_H
#define DCRESETSERVICES_H
#include "Routines/idcresetservices.h"
template<typename T,typename U> class IDCPlayerManager;
class DCInput;
class DCPlayer;
template<typename T,typename U> class IDCIndexController;
struct DCMeta;
class DCIndex;
template<typename T> class IDCMetaManager;
class DCServices;
class DCResetServices : public IDCResetServices
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCMetaManager<DCMeta> MetaManager;
    DCResetServices(DCServices *services);
    virtual void reset() override;
private:
    MetaManager *_metaManager;
    IndexController *_indexController;
    PlayerManager *_playerManager;
};

#endif // DCRESETSERVICES_H
