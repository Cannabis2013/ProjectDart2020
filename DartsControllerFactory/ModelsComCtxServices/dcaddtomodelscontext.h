#ifndef DCADDTOMODELSCONTEXT_H
#define DCADDTOMODELSCONTEXT_H
#include "DCInputSLAs/idcaddtomdsctx.h"
class DCServices;
class QByteArray;
class QJsonObject;
struct DCIndex;
class DCAddToModelsContext : public IDCAddToMdsCtx
{
public:
    DCAddToModelsContext(DCServices *services);
    bool add(DCInput &ipt, AbsDartsCtx *mdsCtx) override;
private:
    DCServices *_services;
};
#endif // DCADDTOMODELCONTEXT_H
