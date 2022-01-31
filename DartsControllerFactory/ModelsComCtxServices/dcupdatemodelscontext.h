#ifndef DCUPDATEMODELSCONTEXT_H
#define DCUPDATEMODELSCONTEXT_H
#include "DCInputSLAs/idcaddtomdsctx.h"
class DCServices;
class QByteArray;
class QJsonObject;
struct DCIndex;
class DCUpdateModelsContext : public IDCAddToMdsCtx
{
public:
    DCUpdateModelsContext(DCServices *services);
    bool add(DCInput &ipt, AbsDartsCtx *mdsCtx) override;
private:
    DCServices *_services;
};
#endif // DCADDTOMODELCONTEXT_H
