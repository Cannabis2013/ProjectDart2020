#ifndef DCJSONTOINPUTMODELS_H
#define DCJSONTOINPUTMODELS_H

#include <DartsController/Contracts/Converters/idcjsontomodels.h>

class QJsonObject;
struct DCInput;
class DCJsonToInputModels : public IDCJsonToModels<DCInput>
{
public:
    Models convert(const QByteArray &byteArray, JsonToModel *jsonToModel) const override;
};
#endif // DCJSONTOINPUTMODELS_H
